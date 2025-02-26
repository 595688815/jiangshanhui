#ifndef DATAFRESHTHREAD_H
#define DATAFRESHTHREAD_H
#include <thread>
#include <mutex>
#include <QSerialPort>
#include <QObject>
#include "Globals/globals.h"

using namespace std;
/*
 * 刷新实时数据线程，与全局数据对接
 * 对数据读写进行管理
 */
class DataFreshThread : public QObject
{
    Q_OBJECT
public:
    DataFreshThread();
    ~DataFreshThread();

    void SetSerialPort(QSerialPort *serialport);

    void StartThread();

    virtual QByteArray EnSendMessage();

    virtual bool AnalyzeRcvData();

    virtual void HandleRcvData();
private:
    std::thread *m_data_fresh_thread;   //线程管理指针
    bool m_thread_quit_flag;            //线程退出管理
    QByteArray m_rcv_buffer;            //接收缓冲区
    int m_send_step;                    //发送步骤管理标志位
    QSerialPort *m_serialport;          //端口
private slots:
    virtual void RcvAllMessage();
};

#endif // DATAFRESHTHREAD_H
