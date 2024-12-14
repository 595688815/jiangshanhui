#ifndef SYSTEMBASESHEET_H
#define SYSTEMBASESHEET_H
#include "systembase.h"
//表单
class CSystemBaseSheet : public CSystemBase
{
public:
    CSystemBaseSheet(){systype=ST_Sheet;}

    QString GetSheetId(){return m_sheet_id;}
    void SetSheetId(QString str){m_sheet_id = str;}
    QString GetSheetName(){return m_sheet_name;}
    void SetSheetName(QString str){m_sheet_name = str;}
private:
    QString m_sheet_id;       //角色ID
    QString m_sheet_name;     //角色名称
};

#endif // SYSTEMBASESHEET_H
