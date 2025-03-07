#include "alarm.h"

Alarm *Alarm::m_instance=nullptr;

Alarm::Alarm()
{
    m_alarm_thread=new QThread;
    connect(m_alarm_thread,&QThread::started,this,&Alarm::run);
}
/*
* 函数名：getInstance
* 参数：无
* 返回：Alarm*
* 功能：返回单例
*/
Alarm* Alarm::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new Alarm();
    }
    return m_instance;
}
/*
* 函数名：getInstance
* 参数：无
* 返回：无
* 功能：线程运行函数，线程伴随程序运行开始开始，程序运行结束结束
*/
void Alarm::run()
{
    //线程开始读取alarm.cfg文件
    QFile file("alarm.cfg");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file alarm.cfg";
        return;
    }
    QList <QPair<uint8_t,QString>> *tmplist=Globals::getInstance()->GetAlarmList();
    while(!file.atEnd())
    {
        QByteArray str=file.readLine();
        if(str.startsWith("//"))    //注释行直接跳过
            continue;
        //筛除干扰字符串
        str.replace("\n","");
        str.replace(";","");

        QPair<uint8_t,QString> unit;
        QList<QByteArray> list=str.split(',');
        if(list.size()==2)
        {
            unit.first=list[0].toInt();
            unit.second=list[1];
            tmplist->push_back(unit);
        }
    }
    file.close();
    while(1)
    {
        for(int i=0;i<tmplist->size();++i)
        {
            if(Globals::getInstance()->GetAlarmStatus()==tmplist->at(i).first)
            {
                qDebug()<<tmplist->at(i).second;
            }
        }
        //报警界面显示周期100ms
        QThread::msleep(1000);
    }
}
