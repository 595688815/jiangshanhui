#ifndef DPLCN_H
#define DPLCN_H
#include "DPLCExt/dplcextbase.h"

class DPLCN : public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool OnRun() override;
    bool Run() override;
};

#endif // DPLCN_H
