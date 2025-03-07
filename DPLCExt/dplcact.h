#ifndef DPLCACT_H
#define DPLCACT_H
#include "DPLCExt/dplcextbase.h"
/*
 * 保留模块
 */
class DPLCAct:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCACT_H
