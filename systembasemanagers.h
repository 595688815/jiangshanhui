#ifndef SYSTEMBASEMANAGERS_H
#define SYSTEMBASEMANAGERS_H
#include "systembase.h"
//管理员
class CSystemBaseManager : public CSystemBase
{
public:
    CSystemBaseManager(){systype=ST_Manager;}

    QString GetAccount(){return m_account;}
    void SetAccount(QString str){m_account = str;}
    QString GetPassword(){return m_pass_word;}
    void SetPassword(QString str){m_pass_word = str;}
private:
    QString m_account;      //账号
    QString m_pass_word;    //密码
};

#endif // SYSTEMBASEMANAGERS_H
