#ifndef FILESERVER_H
#define FILESERVER_H
#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QAbstractSocket>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include "filesocket.h"
#include <QTime>

class FileServer : public QTcpServer
{
public:
    static FileServer* getInstance();

    void incomingConnection(qintptr socketDescriptor);
private:
    //私有化构造函数和析构函数
    FileServer(){}
    ~FileServer(){}
    FileServer(const FileServer&) = delete;
    FileServer& operator=(const FileServer&) = delete;
    //静态成员变量保存唯一实例
    static FileServer* m_instance;
    QList<FileSocket*> m_tcpSocketList;
};



#endif // FILESERVER_H
