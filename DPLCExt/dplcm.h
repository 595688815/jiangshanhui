#ifndef DPLCM_H
#define DPLCM_H
#include "DPLCExt/dplcextbase.h"

class DPLCM : public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    uint32_t GetFreshTime(){return m_fresh_time;}
    void SetFreshTime(uint32_t value){m_fresh_time=value;}

    bool OnRun() override;
    bool Run() override;
private:
    uint32_t m_fresh_time;  //刷新周期，单位：ms
};

#endif // DPLCM_H
