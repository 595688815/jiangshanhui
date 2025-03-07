#ifndef DPLCTRIGGER_H
#define DPLCTRIGGER_H
#include "DPLCExt/dplcextbase.h"
/*
 * 外部触发模块
 */
//IN:
//m_nodein_list[0]:BindAddress
//OUT:
//m_nodeout_list[0]:OUT
class DPLCTrigger:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCTRIGGER_H
