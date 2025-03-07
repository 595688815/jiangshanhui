#include "dplcbase.h"

DPLCBase::DPLCBase(QString name,QString id,uint8_t type,QString desc)
{
    m_name=name;
    m_id=id;
    m_desc=desc;
    m_type=type;
    m_class_creat_flag=false;
}
/*
* 函数名：GetValRead
* 参数：Node
* 返回：sReadVarRet
* 功能：获取读变量对象
*/
sReadVarRet DPLCBase::GetValRead(Node node)
{
    sReadVarPar var;
    var.addr=node.var.idaddr;
    var.length=node.var.length;
    var.num=1;
    var.type=node.var.type;
    sReadVarRet ret=Globals::getInstance()->ReadVar(var);
    return ret;
}
/*
* 函数名：NodeValueToD
* 参数：Node
* 返回：sReadVarRet
* 功能：读变量值转DI、DO变量值
*/
uint8_t DPLCBase::NodeValueToD(Node node)
{
    sReadVarRet ret=GetValRead(node);
    uint8_t ret_v=ret.value[0];
    return ret_v;
}
/*
* 函数名：NodeValueToA
* 参数：Node
* 返回：uint16_t
* 功能：读变量值转AI、AO变量值
*/
uint16_t DPLCBase::NodeValueToA(Node node)
{
    sReadVarRet ret=GetValRead(node);
    uint16_t ret_v=(ret.value[0]<<8)+ret.value[1];
    return ret_v;
}
/*
* 函数名：NodeValueToN
* 参数：Node
* 返回：uint32_t
* 功能：读变量值转F变量值
*/
uint32_t DPLCBase::NodeValueToN(Node node)
{
    sReadVarRet ret=GetValRead(node);
    uint32_t ret_v=(ret.value[0]<<24)+(ret.value[1]<<16)+(ret.value[2]<<8)+(ret.value[3]<<24);
    return ret_v;
}
/*
* 函数名：NodeValueToF
* 参数：Node
* 返回：float
* 功能：读变量值转F变量值
*/
float DPLCBase::NodeValueToF(Node node)
{
    sReadVarRet ret=GetValRead(node);
    uint8_t ch[4];
    ch[0]=ret.value[0];
    ch[1]=ret.value[1];
    ch[2]=ret.value[2];
    ch[3]=ret.value[3];
    float ret_v=*((float*)ch);
    return ret_v;
}
/*
* 函数名：NodeValueToM
* 参数：Node
* 返回：QByteArray
* 功能：读变量值转M变量值
*/
QByteArray DPLCBase::NodeValueToM(Node node)
{
    sReadVarRet ret=GetValRead(node);
    QByteArray ret_v="";
    for(auto item:ret.value)
        ret_v.append(item);
    return ret_v;
}
/*
* 函数名：SetValWrite
* 参数：Node , uint8_t
* 返回：bool
* 功能：写入节点绑定变量
*/
bool DPLCBase::SetValWrite(Node node,uint8_t value)
{
    sWriteVarPar var;
    var.addr=node.var.idaddr;
    var.length=node.var.length;
    var.type=node.var.type;
    var.value.push_back(value);
    if(Globals::getInstance()->WriteVar(var).code==0)
        return true;
    else
        return false;
}
/*
* 函数名：SetValWrite
* 参数：Node,uint16_t
* 返回：bool
* 功能：写入节点绑定变量
*/
bool DPLCBase::SetValWrite(Node node,uint16_t value)
{
    sWriteVarPar var;
    var.addr=node.var.idaddr;
    var.length=node.var.length;
    var.type=node.var.type;
    var.value.push_back((value>>8)&0xff);
    var.value.push_back(value&0xff);
    if(Globals::getInstance()->WriteVar(var).code==0)
        return true;
    else
        return false;
}
/*
* 函数名：SetValWrite
* 参数：Node,uint32_t
* 返回：bool
* 功能：写入节点绑定变量
*/
bool DPLCBase::SetValWrite(Node node,uint32_t value)
{
    sWriteVarPar var;
    var.addr=node.var.idaddr;
    var.length=node.var.length;
    var.type=node.var.type;
    var.value.push_back((value>>24)&0xff);
    var.value.push_back((value>>16)&0xff);
    var.value.push_back((value>>8)&0xff);
    var.value.push_back(value&0xff);
    if(Globals::getInstance()->WriteVar(var).code==0)
        return true;
    else
        return false;
}
/*
* 函数名：SetValWrite
* 参数：Node,float
* 返回：bool
* 功能：写入节点绑定变量
*/
bool DPLCBase::SetValWrite(Node node,float value)
{
    sWriteVarPar var;
    uint8_t ch[4];
    var.addr=node.var.idaddr;
    var.length=node.var.length;
    var.type=node.var.type;
    memcpy(ch,&value,sizeof(value));
    var.value.push_back(ch[0]);
    var.value.push_back(ch[1]);
    var.value.push_back(ch[2]);
    var.value.push_back(ch[3]);
    if(Globals::getInstance()->WriteVar(var).code==0)
        return true;
    else
        return false;
}
/*
* 函数名：SetValWrite
* 参数：Node,QByteArray
* 返回：bool
* 功能：写入节点绑定变量
*/
bool DPLCBase::SetValWrite(Node node,QByteArray value)
{
    sWriteVarPar var;
    var.addr=node.var.idaddr;
    var.length=node.var.length;
    var.type=node.var.type;
    for(auto item:value)
        var.value.push_back((uint8_t)item);
    if(Globals::getInstance()->WriteVar(var).code==0)
        return true;
    else
        return false;
}
/*
* 函数名：CheckClassFlag
* 参数：QString
* 返回：bool
* 功能：检查实例化对象节点正确性
*/
bool DPLCBase::CheckClassFlag(QString msg)
{
    if(!m_class_creat_flag)
    {
        qDebug()<<msg;
        Globals::getInstance()->Logging(msg);
        return false;
    }
    return true;
}
