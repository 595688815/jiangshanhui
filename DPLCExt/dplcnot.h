#ifndef DPLCNOT_H
#define DPLCNOT_H
#include "DPLCExt/dplcextbase.h"
/*
 * 非模块
 */
//IN:
//m_nodein_list[0]:In
//OUT:
//m_nodeout_list[0]:out
class DPLCnot:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCNOT_H
