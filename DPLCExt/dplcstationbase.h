#ifndef DPLCSTATIONBASE_H
#define DPLCSTATIONBASE_H
/*
 * 工位模块基类
 */
#include "DPLCExt/dplcbase.h"

class DPLCStationBase:public DPLCBase
{
    using DPLCBase::DPLCBase;
public:
    DPLCStationBase *p_last_station;    //上工位指针
    enum StationStatus
    {
        None,
        Ready,
        Pick,
        Doing,
        Put,
    };
    QString GetBomID(){return m_bom_id;}
    void SetBomID(QString value){m_bom_id=value;}
    StationStatus m_station_status;
    QString m_bom_id;                   //MES系统BOMID，同一时间一个工位只能加工一个BOM
    bool m_station_enabled=true;    //工位使能开关
public slots:
    void SetReadyStatus(){SetValWrite(m_nodein_list[0],(uint8_t)1);}         //下工位接收上工位发来的信号
};

#endif // DPLCSTATIONBASE_H
