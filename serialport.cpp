#include "serialport.h"
/*
* 函数名：SerialPort
* 参数：无
* 返回：无
* 功能：构造函数
*/
SerialPort::SerialPort(QString portname)
{
    m_serialport = new QSerialPort;
    m_portname = portname;
    m_portrate = "19200";
    m_portparity = "None";
    m_portstop = "One";
    m_portdata = "8";
    connect(m_serialport,&QSerialPort::readyRead,this,&SerialPort::RevMsgToBuf);
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
* 函数名：SendMsg
* 参数：QByteArray
* 返回：bool
* 功能：发送消息至端口
*/
bool SerialPort::SendMsg(QByteArray msg)
{
    if (m_serialport != nullptr)
    {
        QString hexstring = msg.trimmed().replace(" ", "");
        QByteArray ba = QByteArray::fromHex(hexstring.toLocal8Bit());
        if(m_serialport->write(ba)>0)
            return true;
    }
    return false;
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
/*
* 函数名：GetRevBuf
* 参数：无
* 返回：QByteArray
* 功能：截取缓存区
*/
QByteArray SerialPort::GetRevBuf()
{
    return m_rev_buffer;
}
/*
* 函数名：GetRevMsg
* 参数：无
* 返回：无
* 功能：接收消息放入缓存区
*/
void SerialPort::RevMsgToBuf()
{
    QByteArray str=m_serialport->readAll();
    m_rev_buffer.append(str);
    if(AnalyzerMessage())           //采集模块数据接收完毕
    {
        emit RcvMsg(m_rev_buffer);
        ClearList();
    }
}
/*
* 函数名：ClearList
* 参数：无
* 返回：无
* 功能：清空缓冲区
*/
void SerialPort::ClearList()
{
    m_rev_buffer.clear();
}
/*
* 函数名：getCRCH
* 参数：char*,int
* 返回：unsigned char
* 功能：计算CRC校验码
*/
/*
* 函数名：AnalyzerMessage
* 参数：无
* 返回：bool
* 功能：解析采集模块返回数据包是否发送完毕且合法
*/
bool SerialPort::AnalyzerMessage()
{

}
/*
* 函数名：getCRCH
* 参数：char*,int
* 返回：unsigned char
* 功能：计算CRC校验码
*/
unsigned short SerialPort::getCRC(char* buf, int length)
{
    unsigned short wcrc = 0xffff;
    unsigned char temp;

    for (int i = 0; i < length; i++)
    {
        temp = *buf & 0x00ff;
        buf++;
        wcrc ^= temp;
        for (int j = 0; j < 8; j++)
        {
            if (wcrc & 0x0001)
            {
                wcrc >>= 1;
                wcrc ^= 0xA001;
            }
            else
            {
                wcrc >>= 1;
            }
        }
    }
    return wcrc;
}

