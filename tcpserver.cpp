#include "tcpserver.h"
#include <QThread>

Tcpserver::Tcpserver(QObject *parent)
    : QTcpServer{parent}
{}

Tcpserver &Tcpserver::getInstance()
{
    static Tcpserver instance;
    return instance;
}

void Tcpserver::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "new connection";
    QThread *thread = new QThread;

    connect(thread, &QThread::started, [this, socketDescriptor, thread]()
    {
        MyTcpSocket *pTcpSocket = new MyTcpSocket;
        pTcpSocket->moveToThread(thread);

        connect(pTcpSocket, &QTcpSocket::disconnected, this, &Tcpserver::onDisconnected);
        connect(pTcpSocket, &MyTcpSocket::Timeout, this, &Tcpserver::onDisconnected);

        pTcpSocket->setSocketDescriptor(socketDescriptor);
        qDebug()<<"init";
        pTcpSocket->Init();

        m_tcpSocketList.append(pTcpSocket);
        qDebug() << m_tcpSocketList;
        qDebug() << "Socket Thread" << QThread::currentThreadId();
        //Globals::getInstance()->Logging(QString("Socket Thread:%1").arg(QThread::currentThreadId()));
    });

    thread->start();
    qDebug() << "Main Thread" << QThread::currentThreadId();
}

void Tcpserver::onDisconnected()
{
    qDebug()<<"socketdestory";
    MyTcpSocket *socket = qobject_cast<MyTcpSocket*>(sender());
    m_tcpSocketList.removeOne(socket);

    QThread *thread = socket->thread();


    qDebug()<< "m_tcpSocketList"<<m_tcpSocketList;
    // 在socket的线程中调用disconnectFromHost
    QMetaObject::invokeMethod(socket, &MyTcpSocket::disconnectFromHost, Qt::QueuedConnection);
    socket->deleteLater();

    // 连接线程的finished信号到deleteLater槽
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    // 退出线程
    thread->quit();

}
