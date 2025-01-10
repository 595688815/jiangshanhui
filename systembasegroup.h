#ifndef SYSTEMBASEGROUP_H
#define SYSTEMBASEGROUP_H
#include "systembase.h"
//组织架构
class CSystemBaseGroup : public CSystemBase
{
public:
    CSystemBaseGroup(){systype=ST_Group;}

    QString GetGroupname(){return m_group_name;}
    void SetGroupname(QString str){m_group_name = str;}
    QString GetDeplist(){return m_deplist;}
    void SetDeplist(QString str){m_deplist = str;}
private:
    QString m_group_name;    //组织名称
    QString m_deplist;      //部门列表
};

#endif // SYSTEMBASEGROUP_H
