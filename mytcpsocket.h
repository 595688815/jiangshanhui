#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <chrono>
#include <QTimer>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(QObject *parent = nullptr);
    ~MyTcpSocket();
signals:
    void Timeout();
public slots:
    void RecvMsg();
    void SendMsg(QByteArray byteArray);
    void ResetTimeout();
    void OnTimeout();
    void Init();
    bool AnalyzData(QByteArray str);

private:
    QTimer *m_timer;
};

#endif // MYTCPSOCKET_H
