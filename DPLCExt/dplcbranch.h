#ifndef DPLCBRANCH_H
#define DPLCBRANCH_H
#include "DPLCExt/dplcextbase.h"
/*
 * 分支模块
 */
//IN:
//m_nodein_list[0]:in
//OUT:
//m_nodeout_list[0]:out1
//m_nodeout_list[1]:out2
//m_nodeout_list[2]:out3
//m_nodeout_list[3]:out4
//...
class DPLCBranch:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCBRANCH_H
