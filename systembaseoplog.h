#ifndef SYSTEMBASEOPLOG_H
#define SYSTEMBASEOPLOG_H
#include "systembase.h"
//操作记录
class CSystemBaseOpLog : public CSystemBase
{
public:
    CSystemBaseOpLog(){systype=ST_OpLog;}

    QString GetTime(){return m_time;}
    void SetTime(QString str){m_time = str;}
    QString GetUserid(){return m_userid;}
    void SetUserid(QString str){m_userid = str;}
    QString GetMessage(){return m_message;}
    void SetMessage(QString str){m_message = str;}
private:
    QString m_time;     //时间
    QString m_userid;   //当前操作员
    QString m_message;  //操作记录
};

#endif // SYSTEMBASEOPLOG_H
