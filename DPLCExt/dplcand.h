#ifndef DPLCAND_H
#define DPLCAND_H
#include "DPLCExt/dplcextbase.h"
/*
 * 与模块
 */
//IN:
//m_nodein_list[0]:in1
//m_nodein_list[1]:in2
//...
//OUT:
//m_nodeout_list[0]:out
class DPLCAnd:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCAND_H
