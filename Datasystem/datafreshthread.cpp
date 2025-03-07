#include "Datasystem/datafreshthread.h"
#include <QDebug>
/*
* 函数名：DataFreshThread
* 参数：无
* 返回：无
* 功能：构造函数
*/
DataFreshThread::DataFreshThread() {
    m_send_step=0;
    m_thread_quit_flag=false;
    m_rcv_buffer="";
}
/*
* 函数名：~DataFreshThread
* 参数：无
* 返回：无
* 功能：析构函数
*/
DataFreshThread::~DataFreshThread() {
    m_thread_quit_flag=true;
    if(m_data_fresh_thread!=nullptr)
    {
        m_data_fresh_thread->join();
        free(m_data_fresh_thread);
    }
}
/*
* 函数名：SetSerialPort
* 参数：无
* 返回：无
* 功能：设置端口
*/
void DataFreshThread::SetSerialPort(QSerialPort *serialport)
{
    m_serialport=serialport;
}
/*
* 函数名：StartThread
* 参数：无
* 返回：无
* 功能：线程开始
*/
void DataFreshThread::StartThread()
{
    m_data_fresh_thread=new std::thread([this](){
        connect(m_serialport,&QSerialPort::readyRead,this,&DataFreshThread::RcvAllMessage);     //每次触发信号开辟一条线程去处理槽函数
        while(!m_thread_quit_flag)
        {
            if (m_serialport != nullptr)
            {
                if(m_serialport->isOpen())
                {
                    m_serialport_mtx.lock();
                    if(m_serialport->write(EnSendMessage())<1)
                        qDebug()<<"Send Message Fail!";
                    m_serialport_mtx.unlock();
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(250));            //间隔0.25s
        }
    });
}
/*
* 函数名：EnSendMessage
* 参数：无
* 返回：QByteArray
* 功能：封包发送指令
*/
QByteArray DataFreshThread::EnSendMessage()
{
    QByteArray str="";
    switch(m_send_step)
    {

    }
    return str;
}
/*
* 函数名：RcvAllMessage
* 参数：无
* 返回：无
* 功能：开辟线程处理消息的动作
*/
void DataFreshThread::RcvAllMessage()
{
    std::thread([&](){
        m_serialport_mtx.lock();
        m_rcv_buffer.append(m_serialport->readAll());   //逐帧获取
        m_serialport_mtx.unlock();
        //开始处理消息
        if(AnalyzeRcvData())
            HandleRcvData();
    });
}
/*
* 函数名：AnalyzeRcvData
* 参数：无
* 返回：bool
* 功能：分析接收线程的函数
*/
bool DataFreshThread::AnalyzeRcvData()
{
    if(m_rcv_buffer.size()<5)   //ModBus通讯包头+读写标志+数量+CRC校验码最少5位数
    {
        return false;
    }
    if(m_rcv_buffer[0]!=0x01)
    {
        m_rcv_buffer.clear();   //未检测到完整包头，清空垃圾数据
        return false;
    }
    //crc校验
    QByteArray msg=m_rcv_buffer;
    msg.chop(2);
    unsigned short crc =Globals::getInstance()->getCRC(msg.data(),msg.length());
    if(crc!=(m_rcv_buffer[m_rcv_buffer.size()-2]<<8)+m_rcv_buffer[m_rcv_buffer.size()-1])
    {
        qDebug()<<"CRC Fail!";
        return false;
    }
    return true;
}
/*
* 函数名：HandleRcvData
* 参数：无
* 返回：无
* 功能：处理接收数据的函数
*/
void DataFreshThread::HandleRcvData()
{
    //正确接收数据处理动作
    m_variable_mtx.lock();
    //截取有效数据
    QByteArray rcvdata=m_rcv_buffer.mid(3,m_rcv_buffer.size()-5);   //地址+读写标志位+位数+2位CRC校验位
    //根据协议对号入数

    m_variable_mtx.unlock();
}
