#include "serialportserver.h"


SerialPortServer::SerialPortServer() {}

SerialPortServer::~SerialPortServer()
{

}

SerialPortServer &SerialPortServer::getInstance()
{
    static SerialPortServer instance;
    return instance;
}
/*
 * 函数名：AddSerialPort
 * 参数：QString
 * 返回：bool
 * 函数说明：添加端口对象
*/
bool SerialPortServer::AddSerialPort(QString portname)
{
    qDebug()<<"new file connection";
    Globals::getInstance()->Logging(portname + ":new file connection");
    SerialPort *serialport = new SerialPort(portname);
    if(serialport->OpenPort())
    {
        m_serialport_list.append(serialport);
        qDebug()<< portname<<":Add Serial Port Success";
        return true;
    }
    else
    {
        qDebug()<< portname<<":Add Serial Port Fail";
        return false;
    }
}

QStringList SerialPortServer::GetAllComList()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QStringList list;
    // 遍历并打印每个端口的名称
    for (const QSerialPortInfo& port : ports) {
        list.append(port.portName());
    }
    return list;
}
