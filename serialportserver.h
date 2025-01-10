#ifndef SERIALPORTSERVER_H
#define SERIALPORTSERVER_H
#include <QList>
#include "serialport.h"
#include "globals.h"
/*
 * 串口管理类
 */
class SerialPortServer
{
public:
    SerialPortServer();
    ~SerialPortServer();
    static SerialPortServer &getInstance();
    bool AddSerialPort(QString portname);
    void onTimeout();
    QStringList GetAllComList();
private:
    QList<SerialPort*> m_serialport_list;
};

#endif // SERIALPORTSERVER_H
