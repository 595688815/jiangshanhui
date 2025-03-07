#ifndef DPLCPC_H
#define DPLCPC_H
#include "DPLCExt/dplcextbase.h"
/*
 * 带参数控制模块
 */
//IN:
//m_nodein_list[0]:In
//m_nodein_list[1]:Param
//...
//m_nodein_list[n]:ACK
//OUT:
//m_nodeout_list[0]:out
//m_nodeout_list[1]:Param
//...
//m_nodeout_list[n]:Alarm
class DPLCPC:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCPC_H
