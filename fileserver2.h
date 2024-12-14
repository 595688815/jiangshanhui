#ifndef FILESERVER2_H
#define FILESERVER2_H
#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include <QAbstractSocket>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <filesocket.h>
#include <QTime>

#define UPLOAD_FILE          0x0F01      //上传文件命令
#define SYN_FILE_LIST        0x0F02      //同步文件列表命令
#define DOWNLOAD_FILE        0x0F03      //下载文件命令



class FileServer2 : public QTcpServer
{
public:
    FileServer2();
    ~FileServer2();
    static FileServer2 &getInstance();
    void incomingConnection(qintptr socketDescriptor);
    void onDisconnected();
    void onTimeout();
private:
    QList<FileSocket*> m_tcpSocketList;

};



#endif // FILESERVER2_H
