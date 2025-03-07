#include "tcpserver.h"
#include "Filesystem/jsonfile.h"
#include <QThread>

Tcpserver *Tcpserver::m_instance=nullptr;

Tcpserver::Tcpserver()
{

}
/*
* 函数名：getInstance
* 参数：无
* 返回：Tcpserver*
* 功能：返回单例
*/
Tcpserver* Tcpserver::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new Tcpserver();
    }
    return m_instance;
}

void Tcpserver::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "new connection";

    MyTcpSocket *pTcpSocket = new MyTcpSocket;
    m_tcpSocketList.append(pTcpSocket);
    // for(auto item:m_tcpSocketList)
    //     qDebug()<<item;
    //失去连接时销毁对象
    connect(pTcpSocket->m_socket,&QTcpSocket::disconnected,[=](){
        delete pTcpSocket;
        m_tcpSocketList.removeOne(pTcpSocket);
    });
    // connect(m_tcpSocketList[m_tcpSocketList.size()-1]->m_socket,&QTcpSocket::disconnected,[&](){
    //     delete m_tcpSocketList[m_tcpSocketList.size()-1]->m_this_point;
    //     m_tcpSocketList.removeOne(m_tcpSocketList[m_tcpSocketList.size()-1]->m_this_point);
    // });
    pTcpSocket->m_socket->setSocketDescriptor(socketDescriptor);
    pTcpSocket->Init();
    JsonFile::getInstance()->VarToJsonFile();
}

QList<MyTcpSocket*> Tcpserver::GetTcpList()
{
    return m_tcpSocketList;
}

void Tcpserver::onDisconnected()
{
    qDebug()<<"socketdestory";
}
