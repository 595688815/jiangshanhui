#ifndef DPLCRESET_H
#define DPLCRESET_H
#include "DPLCExt/dplcextbase.h"
/*
 * 系统复位模块
 */
//OUT:
//m_nodeout_list[0]:out
class DPLCRESET:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCRESET_H
