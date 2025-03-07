#ifndef DPLCOR_H
#define DPLCOR_H
#include "DPLCExt/dplcextbase.h"
/*
 * 或模块
 */
//IN:
//m_nodein_list[0]:In1
//m_nodein_list[1]:In2
//m_nodein_list[2]:In3
//m_nodein_list[3]:In4
//...
//OUT:
//m_nodeout_list[0]:out
class DPLCor:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCOR_H
