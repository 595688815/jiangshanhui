#ifndef DPLCSC_H
#define DPLCSC_H
#include <QObject>
#include "DPLCExt/dplcss.h"
#include "DPLCExt/dplcds.h"
#include "DPLCExt/dplcextbase.h"
/*
 * 单控模块
 */
//IN:
//m_nodein_list[0]:OPEN
//m_nodein_list[1]:CLOSE
//m_nodein_list[2]:ACK
//OUT:
//m_nodeout_list[0]:out
//m_nodeout_list[1]:Alarm

class DPLCSC:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
private:
    QTimer *m_ack_timer=nullptr;    //回迅计时器
    bool m_timer_open_flag;         //定时器开关标志
    DPLCAckBase *p_ack;             //回迅模块指针
public slots:
    void On_AckTimeout();
};

#endif // DPLCSC_H
