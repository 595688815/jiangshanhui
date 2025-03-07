#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <thread>
#include <QSocketNotifier>
#include <QTcpServer>
#include "Globals/globals.h"
#include "mytcpsocket.h"
#include <QSharedPointer>
#include <QTimer>

class Tcpserver : public QTcpServer
{
    Q_OBJECT
public:
    static Tcpserver* getInstance();
    void incomingConnection(qintptr socketDescriptor);
    void onDisconnected();
    void onTimeout();
    QList<MyTcpSocket*> GetTcpList();

private:
    //私有化构造函数和析构函数
    Tcpserver();
    ~Tcpserver(){}
    Tcpserver(const Tcpserver&) = delete;
    Tcpserver& operator=(const Tcpserver&) = delete;
    //静态成员变量保存唯一实例
    static Tcpserver* m_instance;
    QList<MyTcpSocket*> m_tcpSocketList;
};

#endif // TCPSERVER_H
