#ifndef SYSTEMBASEDATAHIS_H
#define SYSTEMBASEDATAHIS_H
#include "systembase.h"
//历史数据
class CSystemBaseDatahis : public CSystemBase
{
public:
    CSystemBaseDatahis(){systype=ST_DataHis;}

    QString GetDataRtId(){return m_datart_id;}
    void SetDataRtId(QString str){m_datart_id = str;}
    QString GetCount(){return m_count;}
    void SetCount(QString str){m_count = str;}
    QString GetTimeBegin(){return m_time_begin;}
    void SetTimeBegin(QString str){m_time_begin = str;}
    QString GetTimeEnd(){return m_time_end;}
    void SetTimeEnd(QString str){m_time_end = str;}
    QString GetPeriod(){return m_period;}
    void SetPeriod(QString str){m_period = str;}
private:
    QString m_datart_id;        //实时数据ID
    QString m_count;            //数据个数
    QString m_time_begin;       //开始时间
    QString m_time_end;         //结束时间
    QString m_period;           //采集周期
};

#endif // SYSTEMBASEDATAREC_H
