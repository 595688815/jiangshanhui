#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

/*
通讯基类
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
    //通讯部分
    bool SendMsg(QByteArray msg);
    QByteArray GetRevBuf();
    void ClearList();
    bool AnalyzerMessage();
    //CRC校验处理部分
    unsigned short getCRC(char* buf, int length);
    //接口类
    QSerialPort* m_serialport;
private:
    QString m_portname;
    QString m_portrate;
    QString m_portparity;
    QString m_portstop;
    QString m_portdata;

    QByteArray m_rev_buffer;    //数据缓冲区
public slots:
    void RevMsgToBuf();
signals:
    void RcvMsg(QByteArray);
};

#endif // SERIALPORT_H
