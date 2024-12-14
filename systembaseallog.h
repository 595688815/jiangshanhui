#ifndef SYSTEMDATAALLOG_H
#define SYSTEMDATAALLOG_H
#include "systembase.h"
//报警记录
class CSystemBaseAlLog : public CSystemBase
{
public:
    CSystemBaseAlLog(){systype=ST_AlLog;}

    QString GetTime(){return m_time;}
    void SetTime(QString str){m_time = str;}
    QString GetLevel(){return m_level;}
    void SetLevel(QString str){m_level = str;}
    QString GetMessage(){return m_message;}
    void SetMessage(QString str){m_message = str;}
    QString GetSource(){return m_source;}
    void SetSource(QString str){m_source = str;}
private:
    QString m_time;     //时间
    QString m_level;    //优先级
    QString m_message;  //报警信息
    QString m_source;   //报警来源
};

#endif // SYSTEMDATAALLOG_H
