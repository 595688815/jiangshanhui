#ifndef SYSTEMBASESHEETDATA_H
#define SYSTEMBASESHEETDATA_H
#include "systembase.h"
//表单数据集
class CSystemBaseSheetData : public CSystemBase
{
public:
    CSystemBaseSheetData(){systype=ST_SheetData;}

    QString GetSheetId(){return m_sheet_id;}
    void SetSheetId(QString str){m_sheet_id = str;}
    QString GetDataId(){return m_data_id;}
    void SetDataId(QString str){m_data_id = str;}
    QString GetFieldName(){return m_field_name;}
    void SetFieldName(QString str){m_field_name = str;}
    QString GetDataValue(){return m_value;}
    void SetDataValue(QString str){m_value = str;}
private:
    QString m_sheet_id;         //表单ID
    QString m_data_id;          //表单记录ID
    QString m_field_name;       //字段名称
    QString m_value;            //数据值
};

#endif // SYSTEMBASESHEETDATA_H
