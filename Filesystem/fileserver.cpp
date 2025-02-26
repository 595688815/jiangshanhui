#include "fileserver.h"

#include "Datasystem/tcpserver.h"

FileServer2::FileServer2() {}

FileServer2::~FileServer2()
{

}

FileServer2 &FileServer2::getInstance()
{
    static FileServer2 instance;
    return instance;
}

void FileServer2::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"new file connection";
    Globals::getInstance()->Logging("new file connection");
    FileSocket *pTcpSocket = new FileSocket;
    connect(pTcpSocket, &QTcpSocket::disconnected, this, &FileServer2::onDisconnected);
    connect(pTcpSocket, &FileSocket::timeout, this, &FileServer2::onDisconnected);
    pTcpSocket->setSocketDescriptor(socketDescriptor);
    m_tcpSocketList.append(pTcpSocket);
    qDebug()<< m_tcpSocketList;

}

void FileServer2::onDisconnected()
{
    qDebug()<<"FileClient onDisconnected";
    FileSocket *socket = qobject_cast<FileSocket*>(sender());
    m_tcpSocketList.removeOne(socket);
    qDebug()<< "m_tcpSocketList:"<<m_tcpSocketList;
    socket->disconnectFromHost();
    socket->deleteLater();
}

