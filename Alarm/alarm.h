#ifndef ALARM_H
#define ALARM_H
/*
 * 报警模块
 * 管理所有子系统报警，优先于所有程序
 * 开辟一条线程专门用于管理报警信息
 */
#include <QObject>
#include <QThread>
#include <QDebug>
#include "Globals/globals.h"

using namespace std;

class Alarm:public QThread
{
public:
    static Alarm* getInstance();
    QThread *m_alarm_thread;

    void run() override;
    void quit(){m_quit_flag=true;}
private:
    //私有化构造函数和析构函数
    Alarm();
    Alarm(const Alarm&) = delete;
    Alarm& operator=(const Alarm&) = delete;
    //静态成员变量保存唯一实例
    static Alarm* m_instance;
    bool m_quit_flag=false;
};

#endif // ALARM_H
