#include "dplcss.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCSS::OnRun()
{
    if(m_nodein_list.size()!=1 || m_nodeout_list.size()!=1)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    SetValWrite(m_nodein_list[0],uint8_t(0));
    SetValWrite(m_nodeout_list[0],uint8_t(0));
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCSS::Run()
{
    if(!CheckClassFlag("SS模块节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[0])==0)
        return true;
    else
    {
        SetValWrite(m_nodein_list[0],(uint8_t)0);
        SetValWrite(m_nodeout_list[0],(uint8_t)1);
    }
    return true;
}
