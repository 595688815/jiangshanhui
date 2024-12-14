#ifndef SYSTEMBASESYSLOG_H
#define SYSTEMBASESYSLOG_H
#include "systembase.h"
//系统日志
class CSystemBaseSysLog : public CSystemBase
{
public:
    CSystemBaseSysLog(){systype=ST_SysLog;}

    QString GetTime(){return time;}
    void SetTime(QString str){time = str;}
    QString GetType(){return type;}
    void SetType(QString str){type = str;}
    QString GetMessage(){return message;}
    void SetMessage(QString str){message = str;}
private:
    QString time;       //角色计数
    QString type;       //权限
    QString message;    //内容
};

#endif // SYSTEMBASESYSLOG_H
