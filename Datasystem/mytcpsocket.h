#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <chrono>
#include <QTimer>
#include <QMutex>
/*
 * SOCKET通讯类，这里用线程会导致消息发送不出去，暂时未知原因
 */

class MyTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    ~MyTcpSocket();

    QTcpSocket *m_socket;
    MyTcpSocket *m_this_point;
public slots:
    void RecvMsg();
    void SendMsg(QByteArray byteArray);
    void Init();
    bool AnalyzeRcvData();
    void HandleRcvData(QByteArray str);
    void HandleVarRegisterData(QByteArray msg);
    void HandleSysRegisterData(QByteArray msg);
    void ChangeVarRegisterData(QByteArray msg);
    void HandleVarAskReadData(QByteArray msg);
    void HandleVarAskWriteData(QByteArray msg);
    void HandleFirmwareData(QByteArray msg);
    void Test(){qDebug()<<"测试";}

    QByteArray DataPack(QByteArray data);

    uint16_t GetSysID(){return m_sysid;}
private:
    QByteArray m_read_buf;
    QList<QByteArray> m_send_list;
    uint16_t m_sysid;               //每个子系统对应一个TCP实例，分配一个子系统ID
signals:
    void RegisterMsg(QString);
    void RemoveThis();
};

#endif // MYTCPSOCKET_H
