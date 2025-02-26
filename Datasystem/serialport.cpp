#include "serialport.h"
/*
* 函数名：SerialPort
* 参数：无
* 返回：无
* 功能：构造函数
*/
SerialPort::SerialPort(QString portname)
{
    m_serialport = new QSerialPort();
    m_portname = portname;
    m_portrate = "19200";
    m_portparity = "None";
    m_portstop = "One";
    m_portdata = "8";
    m_msg_thread=new DataFreshThread();
    m_msg_thread->SetSerialPort(m_serialport);
}
/*
* 函数名：~SerialPort
* 参数：无
* 返回：无
* 功能：析构函数
*/
SerialPort::~SerialPort()
{

}
/*
* 函数名：GetPortName
* 参数：无
* 返回：QString
* 功能：返回端口ID
*/
QString SerialPort::GetPortName()
{
    return m_portname;
}
/*
* 函数名：GetPortRate
* 参数：无
* 返回：QString
* 功能：返回端口波特率
*/
QString SerialPort::GetPortRate()
{
    return m_portrate;
}
/*
* 函数名：GetPortParity
* 参数：无
* 返回：QString
* 功能：返回端口校验位
*/
QString SerialPort::GetPortParity()
{
    return m_portparity;
}
/*
* 函数名：GetPortData
* 参数：无
* 返回：QString
* 功能：返回端口数据位
*/
QString SerialPort::GetPortData()
{
    return m_portdata;
}
/*
* 函数名：GetPortName
* 参数：无
* 返回：QString
* 功能：返回端口停止位
*/
QString SerialPort::GetPortStop()
{
    return m_portstop;
}
/*
* 函数名：ConfigPort
* 参数：QString,QString,QString,QString,QString
* 返回：无
* 功能：配置端口参数
*/
void SerialPort::ConfigPort(QString name, QString rate, QString parity, QString stop, QString data)
{
    if (m_serialport == nullptr)
        m_serialport = new QSerialPort;
    m_portname = name;
    m_portrate = rate;
    m_portparity = parity;
    m_portstop = stop;
    m_portdata = data;
}
/*
* 函数名：GetAllComList
* 参数：无
* 返回：QStringList
* 功能：获取端口列表
*/
QStringList SerialPort::GetAllComList()
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QStringList list;
    // 遍历并打印每个端口的名称
    for (const QSerialPortInfo& port : ports) {
        list.append(port.portName());
    }
    return list;
}
/*
* 函数名：OpenPort
* 参数：无
* 返回：bool
* 功能：打开端口
*/
bool SerialPort::OpenPort()
{
    m_serialport->setPort(QSerialPortInfo(m_portname));
    m_serialport->setBaudRate(m_portrate.toInt());
    //校验位
    if (m_portparity == "None")
        m_serialport->setParity(QSerialPort::NoParity);
    else if(m_portparity == "Even")
        m_serialport->setParity(QSerialPort::EvenParity);
    else if (m_portparity == "Odd")
        m_serialport->setParity(QSerialPort::OddParity);
    else if (m_portparity == "Space")
        m_serialport->setParity(QSerialPort::SpaceParity);
    else
        m_serialport->setParity(QSerialPort::MarkParity);
    //停止位
    if (m_portstop == "One")
        m_serialport->setStopBits(QSerialPort::OneStop);
    else if (m_portstop == "Two")
        m_serialport->setStopBits(QSerialPort::TwoStop);
    else
        m_serialport->setStopBits(QSerialPort::OneAndHalfStop);
    //数据位
    if (m_portdata == "5")
        m_serialport->setDataBits(QSerialPort::Data5);
    else if (m_portdata == "6")
        m_serialport->setDataBits(QSerialPort::Data6);
    else if (m_portdata == "7")
        m_serialport->setDataBits(QSerialPort::Data7);
    else
        m_serialport->setDataBits(QSerialPort::Data8);
    return m_serialport->open(QSerialPort::ReadWrite);
}
