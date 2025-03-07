#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "datafreshthread.h"

/*
 * 通讯管理类,只管理通讯参数,通讯内容对应具体项目类
 */
class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(QString portname);
    ~SerialPort();
    //初始化接口函数
    void ConfigPort(QString name, QString rate, QString parity, QString stop, QString data);
    QStringList GetAllComList();
    QString GetPortName();
    QString GetPortRate();
    QString GetPortParity();
    QString GetPortStop();
    QString GetPortData();
    bool OpenPort();
    //接口类
    QSerialPort* m_serialport;
private:
    QString m_portname;
    QString m_portrate;
    QString m_portparity;
    QString m_portstop;
    QString m_portdata;

    DataFreshThread *m_msg_thread;   //线程控制类
};

#endif // SERIALPORT_H
