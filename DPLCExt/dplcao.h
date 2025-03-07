#ifndef DPLCAO_H
#define DPLCAO_H
#include "DPLCExt/dplcextbase.h"

class DPLCAO : public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool OnRun() override;
    bool Run() override;
};

#endif // DPLCAO_H
