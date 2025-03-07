#ifndef DPLCCW_H
#define DPLCCW_H
/*
 * 检测工位
 */
#include "dplcstationbase.h"

class DPLCCW:public DPLCStationBase
{
    Q_OBJECT
    using DPLCStationBase::DPLCStationBase;
public:
    bool OnRun() override;
    bool Run() override;
    DPLCStationBase *p_next_ngstation;
    DPLCStationBase *p_next_okstation;
};

#endif // DPLCCW_H
