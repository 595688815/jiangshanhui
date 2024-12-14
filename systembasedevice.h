#ifndef SYSTEMBASEDEVICE_H
#define SYSTEMBASEDEVICE_H
#include "systembase.h"
//设备
class CSystemBaseDevice : public CSystemBase
{
public:
    CSystemBaseDevice(){systype=ST_Device;}

    QString GetName(){return m_name;}
    void SetName(QString str){m_name = str;}
    QString GetState(){return m_state;}
    void SetState(QString str){m_state = str;}
    QString GetStatus(){return m_status;}
    void SetStatus(QString str){m_status = str;}
private:
    QString m_name;         //设备名称
    QString m_state;        //运行状态
    QString m_status;       //设备状态
};

#endif // SYSTEMBASEDEVICE_H
