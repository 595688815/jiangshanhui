#include "fileserver.h"
#include "Datasystem/tcpserver.h"

FileServer *FileServer::m_instance=nullptr;
/*
* 函数名：getInstance
* 参数：无
* 返回：FileServer*
* 功能：返回单例
*/
FileServer* FileServer::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new FileServer();
    }
    return m_instance;
}
/*
* 函数名：incomingConnection
* 参数：qintptr
* 返回：无
* 功能：外部连接事件槽函数
*/
void FileServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug()<<"new file connection";

    FileSocket *pTcpSocket = new FileSocket;
    m_tcpSocketList.append(pTcpSocket);
    //失去连接时销毁对象
    connect(pTcpSocket->m_socket,&QTcpSocket::disconnected,[=](){
        delete pTcpSocket;
        m_tcpSocketList.removeOne(pTcpSocket);
    });
    pTcpSocket->m_socket->setSocketDescriptor(socketDescriptor);
    pTcpSocket->Init();
}

