#include "filesocket.h"
#include "Filesystem/jsonfile.h"
#include <thread>

FileSocket::FileSocket(QObject *parent)
{
    m_sysid=0xffff;     //初始化为空子系统
    m_socket=new QTcpSocket;
    m_this_point=this;
}

FileSocket::~FileSocket()
{
    qDebug()<<"FileSocket deconstructed";
}
/*
 * 函数名：Init
 * 参数：无
 * 返回：无
 * 函数说明：客户端初始化
*/
void FileSocket::Init()
{
    connect(m_socket, &QTcpSocket::readyRead, this, &FileSocket::onReceiveJsonFile);
}
/*
* 函数名：onReceiveJsonFile
* 参数：无
* 返回：无
* 功能：接收JSON文件
*/
void FileSocket::onReceiveJsonFile()
{
    m_revbuf+=m_socket->readAll();
    if(m_revbuf[m_revbuf.size()-1]!='F'&&m_revbuf[m_revbuf.size()-2]!='O'&&m_revbuf[m_revbuf.size()-3]!='E')
        return;
    QFile file("DPLCNodeConfig.json");
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(m_revbuf.mid(0,m_revbuf.size()-3));
    m_revbuf="";
    file.close();
    qDebug()<<"接收到JSON文件";
    Globals::getInstance()->Logging("Json File Recv");
    QString filePath = "DPLCNodeConfig.json";
    if (!JsonFile::getInstance()->ReadJsonFile(filePath))
    {
        qDebug()<<"JSON文件读取失败";
        return;
    }
    DPLCServer::getInstance()->RefreshDPLCConnect();
    m_socket->write("DPLCEND");
}


