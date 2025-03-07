#include "dplcand.h"

/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCAnd::OnRun()
{
    if(m_nodein_list.size()<2 || m_nodeout_list.size()!=1)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    for(auto item:m_nodein_list)
    {
        SetValWrite(item,(uint8_t)0);
    }
    for(auto item:m_nodeout_list)
    {
        SetValWrite(item,(uint8_t)0);
    }
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCAnd::Run()
{
    if(!CheckClassFlag("AND模块节点非法"))
        return false;
    for(auto item:m_nodein_list)
    {
        if(NodeValueToD(item)!=1 && item.p_next!=nullptr)
        {
            return true;
        }
    }
#ifdef TEST
    qDebug()<<"输入全部信号置1";
    qDebug()<<"And模块触发";
    qDebug()<<"输出置1";
    qDebug()<<"输入信号复位";
#endif
    if(!SetValWrite(m_nodeout_list[0],(uint8_t)1))
    {
        qDebug()<<"与模块输出变量写入失败";
        Globals::getInstance()->Logging("与模块输出变量写入失败");
    }
    //复位
    for(auto item:m_nodein_list)
    {
        if(!SetValWrite(item,(uint8_t)0))
        {
            qDebug()<<"与模块输入变量重置失败";
            Globals::getInstance()->Logging("与模块输入变量重置失败");
        }
    }
    return true;
}
