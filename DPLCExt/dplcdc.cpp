#include "dplcdc.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCDC::OnRun()
{
    if(m_nodein_list.size()!=3 || m_nodeout_list.size()!=3)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    if(m_ack_timer==nullptr)
    {
        m_ack_timer=new QTimer;
        connect(m_ack_timer,&QTimer::timeout,this,&DPLCDC::On_AckTimeout);
        m_ack_timer->stop();
    }
    SetValWrite(m_nodein_list[0],(uint8_t)0);
    SetValWrite(m_nodein_list[1],(uint8_t)1);
    m_switch_flag=false;
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCDC::Run()
{
    if(!CheckClassFlag("DC模块节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[0])==1 && NodeValueToD(m_nodein_list[1])==0 && !m_switch_flag)   //开
    {
        m_switch_flag=true;
        SetValWrite(m_nodeout_list[0],(uint8_t)1);
        SetValWrite(m_nodeout_list[1],(uint8_t)1);
        m_ack_timer->start(1000);
    }
    if(NodeValueToD(m_nodein_list[0])==0 && NodeValueToD(m_nodein_list[1])==1 && m_switch_flag)   //关
    {
        m_switch_flag=false;
        SetValWrite(m_nodeout_list[0],(uint8_t)0);
        SetValWrite(m_nodeout_list[1],(uint8_t)0);
        m_ack_timer->start(1000);
    }
    if(NodeValueToD(m_nodein_list[2])==1)   //接收到回迅信号
    {
        m_ack_timer->stop();
        //重置
        SetValWrite(m_nodein_list[2],(uint8_t)0);
    }
    return true;
}
/*
* 函数名：On_AckTimeout
* 参数：无
* 返回：无
* 功能：回迅超时
*/
void DPLCDC::On_AckTimeout()
{
    qDebug()<<"回迅超时";
    SetValWrite(m_nodeout_list[2],(uint8_t)1);  //报警
    m_ack_timer->stop();
}
