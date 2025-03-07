#include "globals.h"

Globals *Globals::m_instance=nullptr;

Globals::Globals()
{
    //开辟内存地址
    m_array_ext=0;
    m_user_define_addr_begin=100;
    for(int i=0;i<ARRAYMAX;++i)
    {
        m_var_value_array.push_back(0x00);
        if(i<100)       //前100个单元为内置单元，程序开启即自动使用
            m_var_status_array.push_back(0xff);
        else
            m_var_status_array.push_back(0x00);
    }
    //读取工位信息
    QFile file_sys("station.cfg");
    if (!file_sys.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open station.cfg.";
        return;
    }
    while(!file_sys.atEnd())
    {
        QByteArray str=file_sys.readLine();
        if(str.startsWith("//"))    //注释行直接跳过
            continue;
        //筛除干扰字符串
        str.replace("\n","");
        str.replace(";","");

        if(str.startsWith("station"))
        {
            m_station_num=(str.split(':'))[1].toInt();
            DebugText("工位号"+QString::number(m_station_num));
        }
    }
    file_sys.close();
}
/*
* 函数名：getInstance
* 参数：无
* 返回：Globals*
* 功能：返回单例
*/
Globals* Globals::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new Globals();
    }
    return m_instance;
}
/*
* 函数名：GetVarType
* 参数：uint8_t，uint8_t，uint8_t
* 返回：char
* 功能：获取变量类型数组
*/
char Globals::GetVarType(uint8_t type,uint8_t id,uint8_t io)
{
    QString name;
    for(auto item_1:m_ioconfig.IO)
    {
        if(type==item_1.type)
        {
            if(io==1)
            {
                for(auto item_2:item_1.input)
                {
                    if(id==item_2.id.toInt())
                        name=item_2.name;
                }
            }
            if(io==2)
            {
                for(auto item_2:item_1.output)
                {
                    if(id==item_2.id.toInt())
                        name=item_2.name;
                }
            }
        }
    }
    for(auto item:m_var_list)
    {
        if(name==item.idname)
            return item.type;
    }
    return 'M';
}
/*
* 函数名：AddVarUnit
* 参数：VarUnit
* 返回：int
* 功能：向注册变量链表末尾插入变量,返回插入结果
*/
int Globals::AddVarUnit(VarUnit var)
{
    for(int i=0;i<m_var_list.size();i++)
    {
        if(m_var_list[i].idname==var.idname)
        {
            return 1;   //错误码1，重复ID
        }
    }
    switch(var.type)    //错误码2，长度类型不匹配
    {
    case 'I':
    case 'O':
        if(var.length!=1)
            return 2;
        break;

    case 'i':
    case 'o':
        if(var.length!=2)
            return 2;
        break;

    case 'F':
    case 'N':
        if(var.length!=4)
            return 2;
        break;

    default:
        break;
    }
    /*if(var.type=='I')
    {
        VarUnit tvar=var;
        tvar.type='O';
        m_var_list.push_back(tvar);
    }
    if(var.type=='O')
    {
        VarUnit tvar=var;
        tvar.type='I';
        m_var_list.push_back(tvar);
    }
    if(var.type=='i')
    {
        VarUnit tvar=var;
        tvar.type='o';
        m_var_list.push_back(tvar);
    }
    if(var.type=='o')
    {
        VarUnit tvar=var;
        tvar.type='i';
        m_var_list.push_back(tvar);
    }*/
    m_var_list.push_back(var);
    return 0;
}
/*
* 函数名：ChangeVarUint
* 参数：VarUnit
* 返回：int
* 功能：改变注册变量链表指定位置成员变量,返回改变结果
*/
int Globals::ChangeVarUint(VarUnit var)
{
    for(int i=0;i<m_var_list.size();i++)
    {
        if(m_var_list[i].idaddr==var.idaddr && m_var_list[i].type==var.type)
        {
            m_var_list[i]=var;
            return 0;
        }
    }
    return 1;   //错误码1：未找到注册变量地址
}
/*
* 函数名：DeleteVarUint
* 参数：VarUnit
* 返回：int
* 功能：删除注册变量链表指定位置成员变量,返回删除结果
*/
int Globals::DeleteVarUint(VarUnit var)
{
    for(int i=0;i<m_var_list.size();i++)
    {
        if(m_var_list[i].idname==var.idname)
        {
            m_var_list.removeAt(i);
            switch (var.type) {
            case 'I':
            case 'O':
                m_var_status_array[var.idaddr/8]=(m_var_status_array[var.idaddr/8]&(~(1<<(var.idaddr%8))));
                break;

            case 'i':
            case 'o':
            case 'F':
            case 'N':
            case 'M':
                for(int i=0;i<var.length;++i)
                    m_var_status_array[var.idaddr*var.length+i]=0x00;
                break;

            default:
                break;
            }
            return 0;
        }
    }
    return 1;   //错误码1：未找到注册变量地址
}
/*
* 函数名：GetVarUnit
* 参数：VarUnit
* 返回：int
* 功能：获取注册变量链表指定位置成员变量,返回获取结果
*/
int Globals::GetVarUnit(VarUnit &var,uint32_t addr)
{
    for(int i=0;i<m_var_list.size();i++)
    {
        if(m_var_list[i].idaddr==addr)
        {
            var = m_var_list[i];
            return 0;
        }
    }
    return 1;   //错误码1：未找到注册变量地址
}
/*
* 函数名：GetVarListSize
* 参数：无
* 返回：uint32_t
* 功能：获取注册变量链表数量,返回获取结果
*/
uint32_t Globals::GetVarListSize()
{
    return m_var_list.size();
}
/*
* 函数名：RegisterAddr
* 参数：uint32_t &,char,uint32_t
* 返回：int
* 功能：注册变量申请地址,得到变量点位,返回申请结果
*/
int Globals::RegisterAddr(uint32_t &addr,char type,uint32_t length)
{
    switch(type)
    {
    case 'I':
    case 'O':
        for(int i=0;i<m_var_status_array.size();)
        {
            if(m_var_status_array[i]==0xff)
            {
                ++i;
            }
            else
            {
                m_var_status_array[i] = (m_var_status_array[i]<<1);
                m_var_status_array[i] += 1;
                addr=i*8;
                for(int j=0;j<8;++j)
                {
                    if((m_var_status_array[i]>>j)&1)
                        addr++;
                }
                addr-=1;        //点位从0开始
                return 0;
            }
        }
        break;

    case 'i':
    case 'o':
        for(int i=0;i<m_var_status_array.size()-1;) //至少需要两个字节且内存地址必须是2的整数倍（点位特性）
        {
            if(m_var_status_array[i]!=0x00
                ||m_var_status_array[i+1]!=0x00
                ||(i%2!=0))
            {
                ++i;
            }
            else
            {
                m_var_status_array[i]=0xff;
                m_var_status_array[i+1]=0xff;
                addr=i/2;
                return 0;
            }
        }
        break;

    case 'F':
    case 'N':
        for(int i=0;i<m_var_status_array.size()-3;) //至少需要四个字节且内存地址必须是4的整数倍（点位特性）
        {
            if(m_var_status_array[i]!=0x00
                ||m_var_status_array[i+1]!=0x00
                ||m_var_status_array[i+2]!=0x00
                ||m_var_status_array[i+3]!=0x00
                ||(i%4!=0))
            {
                ++i;
            }
            else
            {
                m_var_status_array[i]=0xff;
                m_var_status_array[i+1]=0xff;
                m_var_status_array[i+2]=0xff;
                m_var_status_array[i+3]=0xff;
                addr=i/4;
                return 0;
            }
        }
        break;

    default:
        for(int i=0;i<m_var_status_array.size()-length+1;++i) //至少需要N个字节
        {
            int j;
            for(j=0;j<length;++j)
            {
                if(m_var_status_array[i+j]!=0x00)
                    break;
            }
            if(j==length)     //存在一片连续地址空间
            {
                for(j=0;j<length;j++)
                {
                    m_var_status_array[i+j]=0xff;
                    addr=i;
                    return 0;
                }
            }
        }
        break;
    }
    return 1;
}
/*
* 函数名：RegisterVar
* 参数：uint32_t,char,uint32_t,QString
* 返回：int
* 功能：注册变量赋初值,返回赋值结果
*/
int Globals::RegisterVar(uint32_t addr,char type,uint32_t length,QString valueq)
{
    uint32_t valuei=valueq.toUInt();
    float valuef=valueq.toFloat();
    switch(type)
    {
    case 'I':
    case 'O':
        if(valuei==1)
            m_var_value_array[addr/8]=(1<<(addr%8)) | m_var_value_array[addr/8];
        else
            m_var_value_array[addr/8]=(~(1<<(addr%8))) & m_var_value_array[addr/8];
        return 0;

    case 'i':
    case 'o':
        m_var_value_array[addr*2]=valuei/256;
        m_var_value_array[addr*2+1]=valuei%256;
        return 0;

    case 'F':
    case 'N':
        if(type=='N')
        {
            m_var_value_array[addr*4]=(valuei>>24)&0xff;
            m_var_value_array[addr*4+1]=(valuei>>16)&0xff;
            m_var_value_array[addr*4+2]=(valuei>>8)&0xff;
            m_var_value_array[addr*4+3]=valuei&0xff;
        }
        else                //F
        {
            unsigned char *ch=&m_var_value_array[addr*4];
            memcpy(ch,&valuef,4);
            //float f1=*((float*)ch);
            //qDebug()<<f1;
        }
        return 0;

    case 'M':
        for(int j=0;j<valueq.size();j++)
        {
            QByteArray arr=valueq.toLatin1();
            m_var_value_array[addr+j]=arr[j];
        }
        return 0;

    default:
        break;
    }
    return 1;
}
/*
* 函数名：RenameCheck
* 参数：QString,char
* 返回：bool
* 功能：注册变量ID重复性检测,返回检测结果
*/
bool Globals::RenameCheck(QString idname)
{
    for(auto item:m_var_list)
    {
        if(item.idname==idname)
        {
            return false;
        }
    }
    return true;
}
/*
* 函数名：AddSendBuf
* 参数：QByteArray
* 返回：uint32_t
* 功能：往发送BUF里面添加数据
*/
uint32_t Globals::AddSendBuf(QByteArray msg)
{

}
/*
* 函数名：RegisterModule
* 参数：uint16_t
* 返回：int
* 功能：子系统注册接口函数
*/
int Globals::RegisterModule(uint16_t subsysid,uint16_t subsystype)
{

}
/*
* 函数名：ReadVar
* 参数：uint32_t
* 返回：sReadVarRet
* 功能：读变量值接口
*/
sReadVarRet Globals::ReadVar(sReadVarPar var)
{
    sReadVarRet ret;
    uint32_t addr;
    uint8_t bit;
    switch (var.type) {
    case 'I':
    case 'O':
        for(int i=0;i<var.num;++i)
        {
            addr=(var.addr+i)/8;    //内存地址（字节）
            bit=(var.addr+i)%8;          //bit位
            ret.value.push_back((m_var_value_array[addr]>>bit)&1);
        }
        ret.length=1;
        break;

    case 'i':
    case 'o':
        for(int i=0;i<var.num;++i)
        {
            addr=(var.addr+i)*2;    //内存地址（字节）
            ret.value.push_back(m_var_value_array[addr]);
            ret.value.push_back(m_var_value_array[addr+1]);
        }
        ret.length=2;
        break;

    case 'F':
    case 'N':
        for(int i=0;i<var.num;++i)
        {
            addr=(var.addr+i)*4;    //内存地址（字节）
            ret.value.push_back(m_var_value_array[addr]);
            ret.value.push_back(m_var_value_array[addr+1]);
            ret.value.push_back(m_var_value_array[addr+2]);
            ret.value.push_back(m_var_value_array[addr+3]);
        }
        ret.length=4;
        break;

    case 'M':
        for(int i=0;i<var.num;++i)
        {
            addr=var.addr+i*var.length;    //内存地址（字节）
            for(int j=0;j<var.length;++j)
            {
                ret.value.push_back(m_var_value_array[addr+j]);
            }
        }
        ret.length=var.length;
        break;

    default:
        break;
    }
    ret.num=var.num;
    ret.type=var.type;
    ret.addr=var.addr;
    return ret;
}
/*
* 函数名：ReadVar
* 参数：VarUnit
* 返回：sReadVarRet
* 功能：读变量值接口
*/
sReadVarRet Globals::ReadVar(VarUnit var)
{
    sReadVarRet ret;
    sReadVarPar par;
    par.addr=var.idaddr;
    par.length=var.length;
    par.num=1;
    par.type=var.type;
    ret=ReadVar(par);
    return ret;
}
/*
* 函数名：GetValueToD
* 参数：VarUnit
* 返回：uint8_t
* 功能：DI、DO读变量值接口
*/
uint8_t Globals::GetValueToD(VarUnit var)
{
    sReadVarRet ret=ReadVar(var);
    uint8_t ret_v=ret.value[0];
    return ret_v;
}
/*
* 函数名：GetValueToA
* 参数：VarUnit
* 返回：uint16_t
* 功能：读变量值转AI、AO变量值
*/
uint16_t Globals::GetValueToA(VarUnit var)
{
    sReadVarRet ret=ReadVar(var);
    uint16_t ret_v=(ret.value[0]<<8)+ret.value[1];
    return ret_v;
}
/*
* 函数名：GetValueToN
* 参数：VarUnit
* 返回：uint32_t
* 功能：读变量值转F变量值
*/
uint32_t Globals::GetValueToN(VarUnit var)
{
    sReadVarRet ret=ReadVar(var);
    uint32_t ret_v=(ret.value[0]<<24)+(ret.value[1]<<16)+(ret.value[2]<<8)+ret.value[3];
    return ret_v;
}
/*
* 函数名：GetValueToF
* 参数：VarUnit
* 返回：float
* 功能：读变量值转F变量值
*/
float Globals::GetValueToF(VarUnit var)
{
    sReadVarRet ret=ReadVar(var);
    uint8_t ch[4];
    ch[0]=ret.value[0];
    ch[1]=ret.value[1];
    ch[2]=ret.value[2];
    ch[3]=ret.value[3];
    float ret_v=*((float*)ch);
    return ret_v;
}
/*
* 函数名：GetValueToM
* 参数：VarUnit
* 返回：QByteArray
* 功能：读变量值转M变量值
*/
QByteArray Globals::GetValueToM(VarUnit var)
{
    sReadVarRet ret=ReadVar(var);
    QByteArray ret_v="";
    for(auto item:ret.value)
        ret_v.append(item);
    return ret_v;
}
/*
* 函数名：WriteVar
* 参数：sWriteVarPar
* 返回：sWriteVarRet
* 功能：写变量值接口
*/
sWriteVarRet Globals::WriteVar(sWriteVarPar var)
{
    sWriteVarRet ret;

    ret.addr=var.addr;
    ret.code=0;
    if(var.type=='M')
    {
        for(uint32_t i=0;i<var.length;++i)
        {
            if(i>=m_var_value_array.size()-var.addr)
            {
                ret.code=-1;    //批量写入大小大于预设数组大小
                return ret;
            }
            if(i>=var.value.size())
                m_var_value_array[var.addr+i]=0x00;
            else
                m_var_value_array[var.addr+i]=var.value[i];
        }
    }
    for(uint32_t i=0;i<var.value.size();++i)
    {
        if(var.type=='i'||var.type=='o'||var.type=='N'||var.type=='F')
        {
            if(i>=m_var_value_array.size()-var.addr*var.length)
            {
                ret.code=-1;    //批量写入大小大于预设数组大小
                return ret;
            }
            m_var_value_array[i+var.addr*var.length]=var.value[i];
        }
        if(var.type=='I'||var.type=='O')
        {
            if(i>=m_var_value_array.size()-var.addr/8)
            {
                ret.code=-1;    //批量写入大小大于预设数组大小
                return ret;
            }
            if(var.value[i]==0)
                m_var_value_array[(var.addr+i)/8]&=(~(1<<(var.addr+i)%8));
            else
                m_var_value_array[(var.addr+i)/8]|=(1<<(var.addr+i)%8);
        }
    }
    return ret;
}
/*
* 函数名：ReadM
* 参数：sReadMPar
* 返回：sReadMRet
* 功能：读内存接口
*/
sReadMRet Globals::ReadM(sReadMPar var)
{
    sReadMRet ret;



    return ret;
}
/*
* 函数名：WriteM
* 参数：sWriteMPar
* 返回：sWriteMRet
* 功能：写内存接口
*/
sWriteMRet Globals::WriteM(sWriteMPar var)
{
    sWriteMRet ret;



    return ret;
}
/*
* 函数名：TransferVar
* 参数：sTransferVarPar
* 返回：sTransferVarRet
* 功能：传输变量
*/
sTransferVarRet Globals::TransferVar(sTransferVarPar var,MyTcpSocket *pTcpSocket)
{
    sTransferVarRet ret;
    QByteArray msg="";
    msg.append(var.type);
    msg.append((var.length>>8)&0xff);
    msg.append(var.length&0xff);
    msg.append((var.addr>>8)&0xff);
    msg.append(var.addr&0xff);
    for(auto item:var.value)
        msg.append(item);
    pTcpSocket->SendMsg(pTcpSocket->DataPack(msg));

    return ret;
}
/*
* 函数名：ScanVar
* 参数：sScanVarPar
* 返回：sScanVarRet
* 功能：传输变量
*/
sScanVarRet Globals::ScanVar(sScanVarPar var)
{
    sScanVarRet ret;

    return ret;
}
/*
* 函数名：Logging
* 参数：QString
* 返回：无
* 功能：日志生成
*/
void Globals::Logging(QString data)
{
    int i=0;
    QString filename;
    while(1)
    {
        filename="log_"+QString::number(i)+".txt";
        QFileInfo fileInfo(filename);
        if(fileInfo.exists() && fileInfo.size()>1024000)     //1MB
        {
            i++;
            continue;
        }
        else
            break;
    }
    QFile file(filename);
    if (!file.open(QIODevice::Append))
        qDebug() << "Cannot open file for appending";
    QString text="["+GetSysTime()+"]:"+data.toUtf8()+"\n";
    QByteArray ba=text.toUtf8();
    char *ch=ba.data();
    file.write(ch);
    file.close();
}
/*
* 函数名：DebugText
* 参数：QString
* 返回：无
* 功能：调试打印
*/
void Globals::DebugText(QString data)
{
#ifdef TEST
    qDebug()<<data;
#endif
}
/*
* 函数名：GetSysTime
* 参数：无
* 返回：QString
* 功能：返回系统时间，格式：yyyy-mm-dd hh:mm:ss.zzz
*/
QString Globals::GetSysTime()
{
    QDateTime ctime=QDateTime::currentDateTime();
    QString current_time=ctime.toString("yyyy-MM-dd hh:mm:ss.zzz");
    return current_time;
}
/*
* 函数名：GetRandomData
* 参数：int
* 返回：int
* 功能：返回一个定义范围的随机整数
*/
int Globals::GetRandomData(int max)
{

}
/*
* 函数名：getCRCH
* 参数：char*,int
* 返回：unsigned char
* 功能：计算CRC校验码
*/
uint16_t Globals::getCRC(char* buf, int length)
{
    uint16_t wcrc = 0xffff;
    unsigned char temp;

    for (int i = 0; i < length; i++)
    {
        temp = *buf & 0x00ff;
        buf++;
        wcrc ^= temp;
        for (int j = 0; j < 8; j++)
        {
            if (wcrc & 0x0001)
            {
                wcrc >>= 1;
                wcrc ^= 0xA001;
            }
            else
            {
                wcrc >>= 1;
            }
        }
    }
    return wcrc;
}
