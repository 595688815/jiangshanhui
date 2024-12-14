#ifndef SYSTEMBASEUSER_H
#define SYSTEMBASEUSER_H
#include "systembase.h"
//人员
class CSystemBaseUsers : public CSystemBase
{
public:
    CSystemBaseUsers(){systype=ST_Users;}

    QString GetUserid(){return m_userid;}
    void SetUserid(QString str){m_userid = str;}

    QString GetUsername(){return m_username;}
    void SetUsername(QString str){m_username = str;}

    QString GetPassword(){return m_pass_word;}
    void SetPassword(QString str){m_pass_word = str;}

    QString GetDepIDs(){return m_depIDs;}
    void SetDepIDs(QString str){m_depIDs = str;}

    QString GetRoleIDs(){return m_roleIDs;}
    void SetRoleIDs(QString str){m_roleIDs = str;}

    QString GetOpIDs(){return m_opIDs;}
    void SetOpIDs(QString str){m_opIDs = str;}
private:
    QString m_userid;       //人员ID
    QString m_username;     //姓名
    QString m_pass_word;    //密码
    QString m_depIDs;       //部门
    QString m_roleIDs;      //角色
    QString m_opIDs;        //权限
};

#endif // SYSTEMBASEUSER_H
