#ifndef FILESOCKET_H
#define FILESOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <chrono>
#include <QTimer>
#include <QFile>
#include <filesocket.h>
#include <QCoreApplication>
#include <QDir>
#include <QTime>

#include "globals.h"

#define UPLOAD_FILE          0x0F01      //上传文件命令
#define SYN_FILE_LIST        0x0F02      //同步文件列表命令
#define DOWNLOAD_FILE        0x0F03      //下载文件命令
#define DOWNLOAD_CONFIG      0x0F04      //download config



class FileSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit FileSocket(QObject *parent = nullptr);
    ~FileSocket();
    //发送文件和消息（只发文件头）
    void sendFile();

    void sendconfigFile();

    //将远程文件的文件名记录到文本中
    void getRemoteFileList();

    //清除变量内容，否则污染下一次传输
    void clearVar();

    //清除文件路径，只保留文件名
    QString clearFilePath(QString filePath);

signals:
    void timeout();
public slots:


    //发送文件进度（只发文件内容）
    void onUpdateSendProgress(qint64 numBytes);

    //异常错误处理
    void displayError(QAbstractSocket::SocketError socketError);
    void onReceiveProgress();
    void onReceiveJsonFile();

    void resetTimeout();
    void onTimeout();

private:
    QTimer *m_timer;
    QFile         *m_localFile;      //文件句柄
    QString       m_fileName;        //绝对路径文件名称
    qint64        m_fileNameSize;    //文件名大小
    qint64        m_totalBytes;      //传输文件的总大小

    qint64        m_bytesReceived;   //已接收
    QByteArray    m_inBlock;         //输入缓冲区

    qint64        m_bytesWritten;    //已发送字节数
    qint64        m_bytesTobeWrite;  //待发送的字节数
    QByteArray    m_outBlock;        //输出缓冲区

    qint64        m_payLoadSize;     //每次发送数据的大小
    qint64        m_cmd;             //命令标记
    QTime         m_time;            //保留待开发
    QString       controllername;      //for file saving purpose
};

#endif // FILESOCKET_H
