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
        m_var_status_array.push_back(0x00);
    }
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
* 函数名：RegisterVar
* 参数：uint32_t，uint32_t，uint32_t，uint32_t,uint16_t
* 返回：uint32_t
* 功能：注册变量,返回变量地址
*/
uint32_t Globals::RegisterVar(uint32_t modulID,uint32_t varID, uint32_t type,uint32_t freshtime,uint16_t addr)
{
    VarRegisterClass var;
    var.modulID=modulID;    //模块ID
    var.varID=varID;        //变量ID
    var.type=type;          //变量类型
    var.fretime=freshtime;  //刷新间隔
    var.regi_addr=addr;     //寄存器地址

    for(int i=100;i<ARRAYMAX + m_array_ext;++i)
    {
        var.soft_addr=i;    //前100项保留
        switch (type) {
        case TYPE_DI:
            if(m_var_status_array[i]!=0xff)
            {
                m_var_status_array[i]=((m_var_status_array[i]<<1)+1);
                return i;
            }
            break;

        case TYPE_DO:
            if(m_var_status_array[i]!=0xff)
            {
                m_var_status_array[i]=((m_var_status_array[i]<<1)+1);
                return i;
            }
            break;

        case TYPE_AI:
            if(m_var_status_array[i]==0x00)
            {
                m_var_status_array[i]=0xff;
                var.soft_addr=i;
                m_var_register_list.push_back(var);
                return i;
            }
            break;

        case TYPE_AO:
            if(m_var_status_array[i]==0x00)
            {
                m_var_status_array[i]=0xff;
                var.soft_addr=i;
                m_var_register_list.push_back(var);
                return i;
            }
            break;

        case TYPE_N:
            if(i>ARRAYMAX + m_array_ext-4)        //剩余空间不足4个
            {
                Logging("变量注册地址不足");
                QDebug()<<"变量注册地址不足";
                return ARRAYMAX + m_array_ext;
            }
            if(m_var_status_array[i]==0x00
                & m_var_status_array[i+1]==0x00
                & m_var_status_array[i+2]==0x00
                & m_var_status_array[i+3]==0x00)
            {
                m_var_status_array[i]=0xff;
                m_var_status_array[i+1]=0xff;
                m_var_status_array[i+2]=0xff;
                m_var_status_array[i+3]=0xff;
                var.soft_addr=i;
                m_var_register_list.push_back(var);
                return i;
            }
            break;

        case TYPE_F:
            if(i>ARRAYMAX + m_array_ext-4)        //剩余空间不足4个
            {
                Logging("变量注册地址不足");
                QDebug()<<"变量注册地址不足";
                return ARRAYMAX + m_array_ext;
            }
            if(m_var_status_array[i]==0x00
                & m_var_status_array[i+1]==0x00
                & m_var_status_array[i+2]==0x00
                & m_var_status_array[i+3]==0x00)
            {
                m_var_status_array[i]=0xff;
                m_var_status_array[i+1]=0xff;
                m_var_status_array[i+2]=0xff;
                m_var_status_array[i+3]=0xff;
                var.soft_addr=i;
                m_var_register_list.push_back(var);
                return i;
            }
            break;

        default:        //TYPE_M1
            if(i>ARRAYMAX + m_array_ext-(type-TYPE_M0))        //剩余空间不足M个
            {
                Logging("变量注册地址不足");
                QDebug()<<"变量注册地址不足";
                return ARRAYMAX + m_array_ext;
            }
            if(m_var_status_array[i]==0x00
                & m_var_status_array[i+1]==0x00
                & m_var_status_array[i+2]==0x00
                & m_var_status_array[i+3]==0x00)
            {
                m_var_status_array[i]=0xff;
                m_var_status_array[i+1]=0xff;
                m_var_status_array[i+2]=0xff;
                m_var_status_array[i+3]=0xff;
                var.soft_addr=i;
                m_var_register_list.push_back(var);
                return i;
            }
            break;
        }
    }
    Logging("变量注册地址不足");
    QDebug()<<"变量注册地址不足";
    return ARRAYMAX + m_array_ext;
}
/*
* 函数名：ExtVarList
* 参数：uint32_t
* 返回：uint32_t
* 功能：扩展变量注册链表,输入扩展数量（单位：字节），返回变量注册链表总数量
*/
uint32_t Globals::ExtVarList(uint32_t num)
{
    for(int i=0;i<num;++i)
    {
        m_var_value_array.push_back(0x00);
        m_var_status_array.push_back(0x00);
    }
    m_array_ext += num;
    return ARRAYMAX+m_array_ext;
}
/*
* 函数名：LogOffVar
* 参数：VarRegisterClass
* 返回：bool
* 功能：注销变量,返回注销结果
*/
bool Globals::LogOffVar(VarRegisterClass var)
{
    if(var.soft_addr>=ARRAYMAX)     //非法变量地址
    {
        Logging("非法变量地址");
        QDebug()<<"非法变量地址";
    }
    for(auto item : m_var_register_list)
    {
        if(item==var)
        {
            if(!m_var_register_list.removeOne(item))
            {
                Logging("变量存在，但注销失败");
                QDebug()<<"变量存在，但注销失败";
                return false;
            }
        }
    }
    switch (var.type) {
    case TYPE_DI:

        break;

    case TYPE_DO:

        break;

    case TYPE_AI:

        break;

    case TYPE_AO:

        break;

    case TYPE_N:

        break;

    case TYPE_F:

        break;

    default:    //TYPE_M1
        break;
    }
    return true;
}
/*
* 函数名：Logging
* 参数：QString
* 返回：无
* 功能：日志生成
*/
void Globals::Logging(QString data)
{
    QFile file("log.txt");
    if (!file.open(QIODevice::Append))
        qDebug() << "Cannot open file for appending";
    file.write(data.toUtf8()+"\n");
    file.close();
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
unsigned short Globals::getCRC(char* buf, int length)
{
    unsigned short wcrc = 0xffff;
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
