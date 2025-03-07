#include "dplcbranch.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCBranch::OnRun()
{
    if(m_nodein_list.size()!=1 || m_nodeout_list.size()<2)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    SetValWrite(m_nodein_list[0],(uint8_t)0);
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
bool DPLCBranch::Run()
{
    if(!CheckClassFlag("BRANCH模块节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[0])==1)    //分支模块1个输入，N个输出
    {
#ifdef TEST
        qDebug()<<"输入信号置1";
        qDebug()<<"Branch模块触发";
        qDebug()<<"输出全部置1";
        qDebug()<<"输入信号复位";
#endif
        for(auto item:m_nodeout_list)
        {
            SetValWrite(item,(uint8_t)1);
        }
        //复位
        SetValWrite(m_nodein_list[0],(uint8_t)0);
    }
    return true;
}
