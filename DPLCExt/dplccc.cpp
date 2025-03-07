#include "dplccc.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCCC::OnRun()
{
    if(m_nodein_list.size()!=4 || m_nodeout_list.size()!=3)
        m_class_creat_flag=false;
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
    SetValWrite(m_nodein_list[0],(uint8_t)1);   //使能模块
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCCC::Run()
{
    if(!CheckClassFlag("CC模块节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[0])!=1)   //EN模块
    {
        Globals::getInstance()->DebugText("使能信号非1");
        Globals::getInstance()->DebugText("CC模块退出");
        return true;
    }
    if(NodeValueToD(m_nodein_list[1])==1)   //RST模块
    {
        Globals::getInstance()->DebugText("复位信号置1");
        Globals::getInstance()->DebugText("CC模块触发");
        Globals::getInstance()->DebugText("RST输出置1");
        Globals::getInstance()->DebugText("复位信号复位");
        SetValWrite(m_nodein_list[1],(uint8_t)0);
        SetValWrite(m_nodeout_list[0],(uint8_t)1);
    }
    if(NodeValueToD(m_nodein_list[2])==1)   //TRIGGER模块
    {
        Globals::getInstance()->DebugText("触发信号置1");
        Globals::getInstance()->DebugText("CC模块触发");
        Globals::getInstance()->DebugText("DO输出置1");
        Globals::getInstance()->DebugText("触发信号复位");
        SetValWrite(m_nodein_list[2],(uint8_t)0);
        SetValWrite(m_nodeout_list[1],(uint8_t)1);
    }
    if(NodeValueToD(m_nodein_list[3])==1)   //OVER模块
    {
        Globals::getInstance()->DebugText("结束信号置1");
        Globals::getInstance()->DebugText("CC模块触发");
        Globals::getInstance()->DebugText("NEXT输出置1");
        Globals::getInstance()->DebugText("结束信号复位");
        SetValWrite(m_nodein_list[3],(uint8_t)0);
        SetValWrite(m_nodeout_list[2],(uint8_t)1);
    }
    return true;
}
