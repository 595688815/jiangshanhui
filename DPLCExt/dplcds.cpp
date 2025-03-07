#include "dplcds.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCDS::OnRun()
{
    if(m_nodein_list.size()!=2 || m_nodeout_list.size()!=1)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCDS::Run()
{
    if(!CheckClassFlag("DS模块节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[0])==1 && NodeValueToD(m_nodein_list[1])==0)  //开
    {
        SetACKStatus(1);
    }
    else if(NodeValueToD(m_nodein_list[0])==0 && NodeValueToD(m_nodein_list[1])==1)  //关
    {
        SetACKStatus(0);
    }
    else if(NodeValueToD(m_nodein_list[0])==1 && NodeValueToD(m_nodein_list[1])==1)  //错误
    {
        SetACKStatus(3);
    }
    else
    {
        SetACKStatus(2);
    }
    return true;
}
