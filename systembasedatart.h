#ifndef SYSTEMBASEDATART_H
#define SYSTEMBASEDATART_H
#include "systembase.h"
//实时数据
class CSystemBaseDataRt : public CSystemBase
{
public:
    CSystemBaseDataRt(){systype=ST_DataRt;}

    QString GetId(){return m_id;}
    void SetId(QString str){m_id = str;}
    QString GetName(){return m_name;}
    void SetName(QString str){m_name = str;}
    QString GetDatatype(){return m_data_type;}
    void SetDatatype(QString str){m_data_type = str;}
    QString GetValue(){return m_value;}
    void SetValue(QString str){m_value = str;}
    QString GetTime(){return m_time;}
    void SetTime(QString str){m_time = str;}
private:
    QString m_id;           //数据ID
    QString m_name;         //数据名称
    QString m_data_type;    //数据类型
    QString m_value;        //数据值
    QString m_time;         //更新时间
};

#endif // SYSTEMBASEDATART_H
