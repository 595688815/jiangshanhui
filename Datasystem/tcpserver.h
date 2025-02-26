#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include "Globals/globals.h"
#include "mytcpsocket.h"

class Tcpserver : public QTcpServer
{
public:
    explicit Tcpserver(QObject *parent = nullptr);

    static Tcpserver &getInstance();
    void incomingConnection(qintptr socketDescriptor);
    void onDisconnected();
    void onTimeout();

private:
    QList<MyTcpSocket*> m_tcpSocketList;

};

#endif // TCPSERVER_H
