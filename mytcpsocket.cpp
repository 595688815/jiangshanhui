#include "mytcpsocket.h"
#include <QThread>
MyTcpSocket::MyTcpSocket(QObject *parent)
    : QTcpSocket{parent}
{

}

MyTcpSocket::~MyTcpSocket()
{
    delete m_timer;
    m_timer = nullptr;
    qDebug()<<"MyTcpSocket is deconstructed";
}
/*
 * 函数名：Init
 * 参数：无
 * 返回：无
 * 函数说明：客户端初始化
*/
void MyTcpSocket::Init()
{
    qDebug()<<"socket created";
    m_timer = new QTimer(this);
    m_timer->setInterval(172800000);
    connect(m_timer, &QTimer::timeout, this, &MyTcpSocket::OnTimeout);
    connect(this, &QTcpSocket::readyRead, this, &MyTcpSocket::RecvMsg);
    connect(this, &QTcpSocket::readyRead, this, &MyTcpSocket::ResetTimeout);
    m_timer->start();

    qDebug()<<"mytcpsocket in currentThreadId"<<QThread::currentThreadId();
}
/*
 * 函数名：RecvMsg
 * 参数：无
 * 返回：无
 * 函数说明：接收客户端的消息
*/
void MyTcpSocket::RecvMsg()
{
    QByteArray lstr = readAll();
    qDebug()<<lstr;
}
/*
 * 函数名：SendMsg
 * 参数：无
 * 返回：无
 * 函数说明：发送消息给客户端
*/
void MyTcpSocket::SendMsg(QByteArray byteArray)
{
    write(byteArray);
}
/*
 * 函数名：ResetTimeout
 * 参数：无
 * 返回：无
 * 函数说明：重置定时器
*/
void MyTcpSocket::ResetTimeout()
{
    m_timer->start(); // 重置定时器 
}
/*
 * 函数名：OnTimeout
 * 参数：无
 * 返回：无
 * 函数说明：客户端无应答超时处理
*/
void MyTcpSocket::OnTimeout()
{
    qDebug()<<"no signal between client and server,connection is disconnected";
    emit Timeout(); // 发射超时信号
}
/*
 * 函数名：AnalyzData
 * 参数：无
 * 返回：bool
 * 函数说明：分析接收到的数据内容
*/
bool MyTcpSocket::AnalyzData()
{

}
