#ifndef SERIALPORTSERVER_H
#define SERIALPORTSERVER_H
#include <QList>
#include "Datasystem/serialport.h"
#include "Globals/globals.h"
/*
 * 串口设备管理类,只对设备连接和设备ID的列表管理,设备通讯对应具体项目类
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
    QList<SerialPort*> GetAllConnectedSerialPort();
private:
    QList<SerialPort*> m_serialport_list;
};

#endif // SERIALPORTSERVER_H
