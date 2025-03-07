#include "dplccw.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCCW::OnRun()
{
    if(m_nodein_list.size()!=10 || m_nodeout_list.size()!=7)
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
bool DPLCCW::Run()
{
    if(!CheckClassFlag("CW工位节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[1])==1)   //使能状态下
    {
        if(NodeValueToD(m_nodein_list[0])==1)   //准备上料
        {
            m_station_status=Ready;
            SetValWrite(m_nodein_list[0],(uint8_t)0);
            SetValWrite(m_nodeout_list[2],(uint8_t)1);
            Globals::getInstance()->DebugText("CW工位准备好");
        }
        if(NodeValueToD(m_nodein_list[2])==1 && m_station_status==Ready)   //上料准备好
        {
            m_station_status=Pick;
            SetValWrite(m_nodein_list[2],(uint8_t)0);
            SetValWrite(m_nodeout_list[3],(uint8_t)1);
            Globals::getInstance()->DebugText("CW工位上料已准备好");
        }
        if(NodeValueToD(m_nodein_list[3])==1)   //上料完成
        {
            m_station_status=Doing;
            SetValWrite(m_nodein_list[3],(uint8_t)0);
            SetValWrite(m_nodeout_list[4],(uint8_t)1);
            Globals::getInstance()->DebugText("CW工位上料完成");
        }
        if(NodeValueToD(m_nodein_list[4])==1)   //下料准备好
        {
            m_station_status=Put;
            SetValWrite(m_nodein_list[4],(uint8_t)0);
            Globals::getInstance()->DebugText("CW工位下料已准备好");
        }
        if(m_station_status==Put)
        {
            if(NodeValueToD(m_nodein_list[5])==1)   //OK下料准备好
            {
                SetValWrite(m_nodein_list[5],(uint8_t)0);
                SetValWrite(m_nodeout_list[5],(uint8_t)1);
                Globals::getInstance()->DebugText("CW工位OK下料");
            }
            if(NodeValueToD(m_nodein_list[6])==1)   //NG下料准备好
            {
                SetValWrite(m_nodein_list[6],(uint8_t)0);
                SetValWrite(m_nodeout_list[6],(uint8_t)1);
                Globals::getInstance()->DebugText("CW工位NG下料");
            }
        }
        if(NodeValueToD(m_nodein_list[7])==1)   //OK下料完毕
        {
            m_station_status=None;
            SetValWrite(m_nodein_list[7],(uint8_t)0);
            Globals::getInstance()->DebugText("CW工位OK下料完毕");
            //通知NG下工位
            SetValWrite(m_nodeout_list[0],(uint8_t)1);
            p_next_ngstation->SetReadyStatus();
        }
        if(NodeValueToD(m_nodein_list[8])==1)   //NG下料完毕
        {
            SetValWrite(m_nodein_list[8],(uint8_t)0);
            Globals::getInstance()->DebugText("CW工位NG下料完毕");
            //通知NG下工位
            SetValWrite(m_nodeout_list[1],(uint8_t)1);
        }
    }
    return true;
}

