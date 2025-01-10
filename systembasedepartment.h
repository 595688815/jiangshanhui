#ifndef SYSTEMBASEDEPARTMENT_H
#define SYSTEMBASEDEPARTMENT_H
#include "systembase.h"
//部门
class CSystemBaseDepartment : public CSystemBase
{
public:
    CSystemBaseDepartment(){systype=ST_Department;}

    QString GetDepid(){return m_depid;}
    void SetDepid(QString str){m_depid = str;}
    QString GetDepname(){return m_depname;}
    void SetDepname(QString str){m_depname = str;}
    QString GetSubDep(){return m_subDep;}
    void SetSubDep(QString str){m_subDep = str;}
    QString GetBroDep(){return m_broDep;}
    void SetBroDep(QString str){m_broDep = str;}
private:
    QString m_depid;        //部门ID
    QString m_depname;      //部门名称
    QString m_subDep;       //下级部门ID
    QString m_broDep;       //同级部门ID
};

#endif // SYSTEMBASEDEPARTMENT_H
