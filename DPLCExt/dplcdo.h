#ifndef DPLCDO_H
#define DPLCDO_H
#include "DPLCExt/dplcextbase.h"

class DPLCDO : public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool OnRun() override;
    bool Run() override;
};

#endif // DPLCDO_H
