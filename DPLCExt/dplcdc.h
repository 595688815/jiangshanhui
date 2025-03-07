#ifndef DPLCDC_H
#define DPLCDC_H
#include "DPLCExt/dplcextbase.h"
/*
 * 双控模块
 */
//IN:
//m_nodein_list[0]:OPEN
//m_nodein_list[1]:CLOSE
//m_nodein_list[2]:SS
//OUT:
//m_nodeout_list[0]:out1
//m_nodeout_list[1]:out2
//m_nodeout_list[2]:ALARM
class DPLCDC:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
private:
    QTimer *m_ack_timer=nullptr;        //回迅计时器
    bool m_switch_flag;           //开关标志位
private slots:
    void On_AckTimeout();
signals:
    void Sig_AckTimeout();
};

#endif // DPLCDC_H
