#include "dplcpw.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCPW::OnRun()
{
    if(m_nodein_list.size()!=6 || m_nodeout_list.size()!=5)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    m_station_status=None;
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCPW::Run()
{
    if(!CheckClassFlag("PW工位节点非法"))
        return false;
    if(true)//m_station_enabled)   //使能状态下
    {
        //Globals::getInstance()->DebugText("PW工位进入使能");
        if(NodeValueToD(m_nodein_list[0])==1 || m_nodein_list[0].p_next==nullptr)   //上工位准备好
        {
            m_station_status=Ready;
            SetValWrite(m_nodein_list[0],(uint8_t)0);
            Globals::getInstance()->DebugText("PW工位已准备好");
        }
        if(NodeValueToD(m_nodein_list[1])==1 && m_station_status==Ready)   //准备好
        {
            SetValWrite(m_nodein_list[1],(uint8_t)0);
            SetValWrite(m_nodeout_list[1],(uint8_t)1);
            Globals::getInstance()->DebugText("PW工位已准备好");
        }
        if(NodeValueToD(m_nodein_list[2])==1)   //上料准备好
        {
            m_station_status=Pick;
            SetValWrite(m_nodein_list[2],(uint8_t)0);
            SetValWrite(m_nodeout_list[2],(uint8_t)1);
            Globals::getInstance()->DebugText("PW工位上料已准备好");
        }
        if(NodeValueToD(m_nodein_list[3])==1)   //上料完成
        {
            m_station_status=Doing;
            SetValWrite(m_nodein_list[3],(uint8_t)0);
            SetValWrite(m_nodeout_list[3],(uint8_t)1);
            Globals::getInstance()->DebugText("PW工位上料完成");
        }
        if(NodeValueToD(m_nodein_list[4])==1)   //下料准备好
        {
            m_station_status=Put;
            SetValWrite(m_nodein_list[4],(uint8_t)0);
            SetValWrite(m_nodeout_list[4],(uint8_t)1);
            Globals::getInstance()->DebugText("PW工位下料已准备好");
        }
        if(NodeValueToD(m_nodein_list[5])==1)   //已下料
        {
            m_station_status=None;
            SetValWrite(m_nodein_list[5],(uint8_t)0);
            SetValWrite(m_nodeout_list[0],(uint8_t)1);
            Globals::getInstance()->DebugText("PW工位已下料");
        }
    }
    return true;
}

