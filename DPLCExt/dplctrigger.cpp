#include "dplctrigger.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCTrigger::OnRun()
{
    if(m_nodein_list.size()!=1 || m_nodeout_list.size()!=1)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    SetValWrite(m_nodeout_list[0],(uint8_t)0);
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCTrigger::Run()
{
    if(!CheckClassFlag("TRIGGER模块节点非法"))
        return false;
    //接收到信息
    if(NodeValueToD(m_nodein_list[0])==1)
    {
#ifdef TEST
        qDebug()<<"触发信号置1";
        qDebug()<<"TRIGGER模块触发";
        qDebug()<<"输出置1";
        qDebug()<<"触发信号复位";
#endif
        if(!SetValWrite(m_nodeout_list[0],(uint8_t)1))
        {
            qDebug()<<"TRIGGER模块输出置1失败";
            Globals::getInstance()->Logging("TRIGGER模块输出置1失败");
            return true;
        }
        if(!SetValWrite(m_nodein_list[0],(uint8_t)0))
        {
            qDebug()<<"TRIGGER触发复位失败";
            Globals::getInstance()->Logging("TRIGGER触发复位失败");
            return true;
        }
    }
    return true;
}
