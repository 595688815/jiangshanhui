#ifndef DPLCPW_H
#define DPLCPW_H
/*
 * 加工工位
 */
#include "dplcstationbase.h"
class DPLCPW:public DPLCStationBase
{
    Q_OBJECT
    using DPLCStationBase::DPLCStationBase;
public:
    bool OnRun() override;
    bool Run() override;
    DPLCStationBase *p_next_station;    //下工位指针
};

#endif // DPLCPW_H
