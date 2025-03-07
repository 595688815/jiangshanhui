#include "mytcpsocket.h"
#include "Filesystem/jsonfile.h"
#include <QCoreApplication>

MyTcpSocket::MyTcpSocket(QObject *parent)
{
    m_sysid=0xffff;     //初始化为空子系统
    m_socket=new QTcpSocket;
    m_this_point=this;
}

MyTcpSocket::~MyTcpSocket()
{
    qDebug()<<"MyTcpSocket is deconstructed";
}
/*
 * 函数名：Init
 * 参数：无
 * 返回：无
 * 函数说明：客户端初始化
*/
void MyTcpSocket::Init()
{
    connect(m_socket, &QTcpSocket::readyRead, this, &MyTcpSocket::RecvMsg);
}
/*
 * 函数名：RecvMsg
 * 参数：无
 * 返回：无
 * 函数说明：接收客户端的消息
*/
void MyTcpSocket::RecvMsg()
{
    m_read_buf += m_socket->readAll();
    if(AnalyzeRcvData())
    {
        HandleRcvData(m_read_buf);
        m_read_buf="";
    }
}
/*
 * 函数名：DataPack
 * 参数：QByteArray
 * 返回：QByteArray
 * 函数说明：数据块打包功能
*/
QByteArray MyTcpSocket::DataPack(QByteArray data)
{
    //回传数据
    QByteArray msg="";
    msg.append(0x40);               //@
    //数据块长度
    msg.append(data.size()/256);
    msg.append(data.size()%256);
    msg.append(data);
    uint16_t crc = Globals::getInstance()->getCRC(msg.data(),msg.size());
    msg.append(crc/256);
    msg.append(crc%256);
    msg.append(0x0d);
    return msg;
}
/*
 * 函数名：AnalyzeRcvData
 * 参数：QByteArray
 * 返回：bool
 * 函数说明：验证接收数据合法性
*/
bool MyTcpSocket::AnalyzeRcvData()
{
    if(m_read_buf.isEmpty())
        return false;
    //数据格式
    //@开头
    if(!m_read_buf.startsWith("@"))             //数据缺失，清空缓存垃圾数据
    {
        m_read_buf="";
        return false;
    }
    //长度
    if(m_read_buf.length()<7)   //未接收完毕
        return false;
    uint32_t tlenth=(m_read_buf[1]<<8)+m_read_buf[2];
    if(m_read_buf.length()<tlenth+6)
        return false;
    //CRC校验码转16进制数比较
    unsigned short crc =Globals::getInstance()->getCRC((m_read_buf.mid(0,m_read_buf.size()-3)).data(),m_read_buf.size()-3);
    uint16_t crc_16=(m_read_buf[m_read_buf.size()-3]<<8)+(m_read_buf[m_read_buf.size()-2]&0xff);
    if(crc!=crc_16)   //CRC校验失败，数据清空
    {
        m_read_buf="";
        return false;
    }
    return true;
}
/*
 * 函数名：HandleRcvData
 * 参数：QList<QByteArray>
 * 返回：无
 * 函数说明：处理接收到的客户端消息
*/
void MyTcpSocket::HandleRcvData(QByteArray str)
{
    //@+数据长度+数据块+CRC+结束符
    QByteArray msg = str.mid(3,str[1]*16+str[2]);
    if(msg.startsWith(0x01))            //子系统注册接口
    {
        HandleSysRegisterData(msg);
    }
    else if(m_sysid==0xffff)
    {
        QByteArray str;
        str.append(0xff);
        SendMsg(DataPack(str));          //未注册子系统，不能进行其他操作
        return;
    }
    if(msg.startsWith(0x02))            //变量注册接口
    {
        HandleVarRegisterData(msg);
    }
    if(msg.startsWith(0x12))            //变量修改接口
    {
        ChangeVarRegisterData(msg);
    }
    if(msg.startsWith(0x03))            //读变量接口
    {
        HandleVarAskReadData(msg);
    }
    if(msg.startsWith(0x04))
    {
        HandleVarAskWriteData(msg);     //写变量接口
    }
}
/*
 * 函数名：HandleSysRegisterData
 * 参数：QByteArray
 * 返回：无
 * 函数说明：处理子系统注册
*/
void MyTcpSocket::HandleSysRegisterData(QByteArray byteArray)
{
    //变量注册标志-子系统ID
    QByteArray data="";
    if(m_sysid!=0xffff)     //已注册
    {
        qDebug()<<"子系统ID已注册";
        data.append(0x01);
        data.append(0xff);
        SendMsg(DataPack(data));
    }
    else
    {
        if((byteArray[1]<<8)+(byteArray[2]&0xff)==0)
        {
            qDebug()<<"子系统ID非法";
            data.append(0x01);
            data.append(0xff);
            SendMsg(DataPack(data));
            return;
        }
        m_sysid=(byteArray[1]<<8)+(byteArray[2]&0xff);
        data.append(0x01);
        data.append((char)0x00);
        SendMsg(DataPack(data));
        qDebug()<<"子系统ID:"<<m_sysid<<"注册成功";
    }
}
/*
 * 函数名：HandleVarRegisterData
 * 参数：QByteArray
 * 返回：无
 * 函数说明：处理变量注册信息
*/
void MyTcpSocket::HandleVarRegisterData(QByteArray byteArray)
{
    //变量注册标志-ID长度-ID-变量类型-变量长度-变量描述
    VarUnit var_unit;
    var_unit.sysid = m_sysid;
    //第一部分:0x02+变量ID                msg[0]
    if((uint8_t)byteArray[1]==0)
    {
        //qDebug()<<"this tcp is "<<m_socket;
        JsonFile::getInstance()->VarToJsonFile(this);       //只获取变量注册表
        return;
    }
    var_unit.idname=byteArray.mid(2,(uint8_t)byteArray[1]);
    //第二部分:变量类型+变量长度+变量说明       msg[1]
    QByteArray part2=byteArray.mid((uint8_t)byteArray[1]+2,byteArray.size()-((uint8_t)byteArray[1]+2));
    var_unit.type=part2[0];
    var_unit.length=part2[1]*16+part2[2];
    var_unit.desc=part2.mid(3,part2.size()-3);
    if((0 !=Globals::getInstance()->RegisterAddr(var_unit.idaddr,var_unit.type,var_unit.length))|| !Globals::getInstance()->RenameCheck(var_unit.idname))
    {
        emit RegisterMsg("注册失败");
        qDebug()<<"注册失败";
        QByteArray ret;
        ret.append(0xff);
        SendMsg(DataPack(ret));
        return;
    }
    Globals::getInstance()->AddVarUnit(var_unit);       //变量注册成功
    JsonFile::getInstance()->VarToJsonFile();
}
/*
 * 函数名：ChangeVarRegisterData
 * 参数：QByteArray
 * 返回：无
 * 函数说明：修改变量注册信息
*/
void MyTcpSocket::ChangeVarRegisterData(QByteArray byteArray)
{
    //变量修改标志-ID长度-ID-变量地址-变量类型-变量长度-变量描述
    VarUnit var_unit;
    //第一部分:0x12+变量ID                msg[0]
    var_unit.idname=byteArray.mid(2,(uint8_t)byteArray[1]);
    //第二部分:变量地址+变量类型+变量长度+变量说明       msg[1]
    QByteArray part2=byteArray.mid((uint8_t)byteArray[1]+2,byteArray.size()-((uint8_t)byteArray[1]+2));
    var_unit.idaddr=(part2[0]<<8)+(part2[1]&0xff);
    var_unit.type=part2[2];
    var_unit.desc=part2.mid(3,part2.size()-3);
    for(auto item:Globals::getInstance()->GetVarList())
    {
        if(item.idaddr==var_unit.idaddr && item.type==var_unit.type)
        {
            var_unit.sysid=item.sysid;
            var_unit.length=item.length;
        }
    }
    if(1==Globals::getInstance()->ChangeVarUint(var_unit))
    {
        QByteArray ret;
        ret.append(0xff);
        SendMsg(DataPack(ret));
        return;
    }
    JsonFile::getInstance()->VarToJsonFile();
}
/*
 * 函数名：HandleVarAskData
 * 参数：QByteArray
 * 返回：无
 * 函数说明：处理变量读请求信息
*/
void MyTcpSocket::HandleVarAskReadData(QByteArray byteArray)
{
    //变量修改标志-变量类型-变量长度-变量地址-变量数量
    sReadVarPar var;
    var.type=byteArray[1];
    var.length=(byteArray[2]<<8)+byteArray[3];
    var.addr=(byteArray[4]<<8)+byteArray[5];
    var.num=(byteArray[6]<<8)+byteArray[7];
    sReadVarRet ret= Globals::getInstance()->ReadVar(var);
    //数据块打包
    QByteArray data;                //数据块
    data.append(0x03);              //0x03
    data.append(ret.type);          //type
    data.append(ret.length/256);    //length
    data.append(ret.length%256);
    data.append(ret.addr/256);      //addr
    data.append(ret.addr%256);
    data.append(ret.num/256);       //num
    data.append(ret.num%256);
    for(int i=0;i<ret.value.size();++i)
        data.append(ret.value[i]);  //data
    SendMsg(DataPack(data));
}
/*
 * 函数名：HandleVarAskWriteData
 * 参数：QByteArray
 * 返回：无
 * 函数说明：处理变量写请求信息
*/
void MyTcpSocket::HandleVarAskWriteData(QByteArray byteArray)
{
    //变量修改标志-变量类型-变量长度-变量地址-写入值队列
    sWriteVarPar var;
    var.type=byteArray[1];
    var.length=(byteArray[2]<<8)+(byteArray[3]&0xff);
    var.addr=(byteArray[4]<<8)+(byteArray[5]&0xff);
    for(int i=6;i<byteArray.size();++i)
    {
        var.value.push_back(byteArray[i]);
    }
    //调用接口
    sWriteVarRet ret=Globals::getInstance()->WriteVar(var);
    QByteArray msg="";
    if(ret.code==0)
    {
        msg.append(0x04);
        msg.append(ret.addr/256);
        msg.append(ret.addr%256);
    }
    else
    {
        msg.append(0xff);
    }
    SendMsg(DataPack(msg));
    for(auto var_unit:Globals::getInstance()->GetVarList())
    {
        //如果非变量注册系统修改了变量值则会通知变量注册子系统（内置变量不会通知）
        if(var_unit.idaddr==ret.addr
            && var_unit.type==ret.type
            && m_sysid!=var_unit.sysid
            && var_unit.sysid>1000)
        {
            for(auto tcp_unit:Tcpserver::getInstance()->GetTcpList())
            {
                if(tcp_unit->m_sysid==var_unit.sysid)
                {
                    sTransferVarPar par;
                    par.addr=var_unit.idaddr;
                    par.length=var_unit.length;
                    par.type=var_unit.type;
                    for(int i=0;i<var.value.size();++i)
                    {
                        par.value.push_back(var.value[i]);
                    }
                    Globals::getInstance()->TransferVar(par,tcp_unit);
                }
            }
        }
    }
}
/*
 * 函数名：HandleFirmwareData
 * 参数：QByteArray
 * 返回：无
 * 函数说明：处理固件返回信息
*/
void MyTcpSocket::HandleFirmwareData(QByteArray byteArray)
{

}
/*
 * 函数名：SendMsg
 * 参数：无
 * 返回：void
 * 函数说明：线程发送消息给客户端
*/
void MyTcpSocket::SendMsg(QByteArray byteArray)
{
    m_socket->write(byteArray);
}
