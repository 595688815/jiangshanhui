#ifndef SYSTEMBASEDATAREC_H
#define SYSTEMBASEDATAREC_H
#include "systembase.h"
//数据记录
class CSystemBaseDatarec : public CSystemBase
{
public:
    CSystemBaseDatarec(){systype=ST_DataRec;}

    QString GetDataRtId(){return m_datart_id;}
    void SetDataRtId(QString str){m_datart_id = str;}
    QString GetRecVale(){return m_value;}
    void SetRecValue(QString str){m_value = str;}
    QString GetTime(){return m_time;}
    void SetTime(QString str){m_time = str;}
private:
    QString m_datart_id;        //数据ID
    QString m_value;            //数据值
    QString m_time;             //更新时间
};

#endif // SYSTEMBASEDATAREC_H
