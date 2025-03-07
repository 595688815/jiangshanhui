#include "dplcsc.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCSC::OnRun()
{
    if(m_nodein_list.size()!=3 || m_nodeout_list.size()!=2)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    if(m_ack_timer==nullptr)
    {
        m_ack_timer=new QTimer;
        connect(m_ack_timer,&QTimer::timeout,this,&DPLCSC::On_AckTimeout);
        m_ack_timer->stop();
    }
    //回迅模块指针指向回迅节点连接的回迅模块节点父指针对象
    p_ack=dynamic_cast<DPLCAckBase*>(m_nodein_list[2].p_next->p_father);
    SetValWrite(m_nodein_list[0],(uint8_t)0);
    SetValWrite(m_nodein_list[1],(uint8_t)0);
    m_timer_open_flag=false;
    m_ack_timer->stop();
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCSC::Run()
{
    if(!CheckClassFlag("SC模块节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[0])==1 && NodeValueToD(m_nodein_list[1])==0)   //开
    {
        qDebug()<<"SC模块打开";
        if(!m_timer_open_flag)
        {
            m_ack_timer->start(1000);
            m_timer_open_flag=true;
        }
        SetValWrite(m_nodeout_list[0],(uint8_t)1);
        //通知单路回迅模块
        if(1==p_ack->ReturnACKStatus())
        {
            m_ack_timer->stop();
            //重置
            SetValWrite(m_nodein_list[0],(uint8_t)0);
            SetValWrite(m_nodein_list[1],(uint8_t)0);
            m_timer_open_flag=false;
        }
    }
    else if(NodeValueToD(m_nodein_list[0])==0 && NodeValueToD(m_nodein_list[1])==1)   //关
    {
        qDebug()<<"SC模块关闭";
        if(!m_timer_open_flag)
        {
            m_ack_timer->start(1000);
            m_timer_open_flag=true;
        }
        SetValWrite(m_nodeout_list[0],(uint8_t)0);
        //通知单路回迅模块
        if(0==p_ack->ReturnACKStatus())
        {
            m_ack_timer->stop();
            //重置
            SetValWrite(m_nodein_list[0],(uint8_t)0);
            SetValWrite(m_nodein_list[1],(uint8_t)0);
            m_timer_open_flag=false;
        }
    }
    else if(NodeValueToD(m_nodein_list[0])==1 && NodeValueToD(m_nodein_list[1])==1 )   //触发报警模块
    {
        SetValWrite(m_nodeout_list[1],(uint8_t)1);
        qDebug()<<"报警模块";
    }
    return true;
}
/*
* 函数名：On_AckTimeout
* 参数：无
* 返回：无
* 功能：回迅超时
*/
void DPLCSC::On_AckTimeout()
{
    qDebug()<<"回迅超时";
    SetValWrite(m_nodeout_list[1],(uint8_t)1);  //报警
    m_ack_timer->stop();
}
