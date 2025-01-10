#ifndef SYSTEMBASESHEETFIELD_H
#define SYSTEMBASESHEETFIELD_H
#include "systembase.h"
//表单字段
class CSystemBaseSheetField : public CSystemBase
{
public:
    CSystemBaseSheetField(){systype=ST_SheetField;}

    QString GetSheetId(){return m_sheet_id;}
    void SetSheetId(QString str){m_sheet_id = str;}
    QString GetFieldName(){return m_field_name;}
    void SetFieldName(QString str){m_field_name = str;}
    QString GetDataRtId(){return m_datart_id;}
    void SetDataRtId(QString str){m_datart_id = str;}
private:
    QString m_sheet_id;         //表单ID
    QString m_field_name;       //字段名称
    QString m_datart_id;        //字段数据对应的实时数据ID
};

#endif // SYSTEMBASESHEETFIELD_H
