#ifndef DPLCF_H
#define DPLCF_H
#include "DPLCExt/dplcextbase.h"

class DPLCF : public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool OnRun() override;
    bool Run() override;
};

#endif // DPLCF_H
