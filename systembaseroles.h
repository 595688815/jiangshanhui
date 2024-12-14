#ifndef SYSTEMBASEROLES_H
#define SYSTEMBASEROLES_H
#include "systembase.h"
//角色
class CSystemBaseRoles : public CSystemBase
{
public:
    CSystemBaseRoles(){systype=ST_Roles;}

    QString GetRoleid(){return m_roleid;}
    void SetRoleid(QString str){m_roleid = str;}
    QString GetRolename(){return m_rolename;}
    void SetRolename(QString str){m_rolename = str;}
    QString GetRolesCnt(){return m_rolesCnt;}
    void SetRolesCnt(QString str){m_rolesCnt = str;}
    QString GetOpIDs(){return m_opIDs;}
    void SetOpIDs(QString str){m_opIDs = str;}
private:
    QString m_roleid;       //角色ID
    QString m_rolename;     //角色名称
    QString m_rolesCnt;     //角色计数
    QString m_opIDs;        //权限
};

#endif // SYSTEMBASEROLES_H
