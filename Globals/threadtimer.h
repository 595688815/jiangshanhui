#ifndef THREADTIMER_H
#define THREADTIMER_H
/*
 * 线程定时器类
 */
#include <QTimer>
#include <QThread>
#include <QObject>
#include <QDateTime>
#include <QRandomGenerator>
#include "globals.h"

class ThreadTimer  : public QThread
{
    Q_OBJECT
public:
    ThreadTimer(QObject *parent = nullptr) : QThread(parent) {}

protected:
    void run() override {
        QTimer timer;
        QObject::connect(&timer, &QTimer::timeout, [](){
            QDateTime currentDateTime = QDateTime::currentDateTime();
            uint16_t data[6];
            //qDebug() << "当前日期时间：" << currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
            data[0]= currentDateTime.toString("yyyy").toInt();
            data[1]= currentDateTime.toString("MM").toInt();
            data[2]= currentDateTime.toString("dd").toInt();
            data[3]= currentDateTime.toString("HH").toInt();
            data[4]= currentDateTime.toString("mm").toInt();
            data[5]= currentDateTime.toString("ss").toInt();
            sWriteVarPar par;
            par.length=2;
            par.type='i';
            for(int i=0;i<6;++i)
            {
                par.addr=i+4;
                par.value.push_back((data[i]>>8)&0xff);
                par.value.push_back(data[i]&0xff);
                Globals::getInstance()->WriteVar(par);
                par.value.clear();
            }
            QRandomGenerator gen=QRandomGenerator::securelySeeded();
            uint32_t rand=gen.bounded(0,1000);
            //qDebug()<<rand;
            par.length=4;
            par.type='N';
            par.addr=1;
            par.value.push_back((rand>>24)&0xff);
            par.value.push_back((rand>>16)&0xff);
            par.value.push_back((rand>>8)&0xff);
            par.value.push_back(rand&0xff);
            Globals::getInstance()->WriteVar(par);
        });
        timer.start(1000); // 1秒触发一次
        exec(); // 启动事件循环，保持线程运行状态
    }
};

#endif // THREADTIMER_H
