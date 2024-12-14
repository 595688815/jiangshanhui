#include "globals.h"

Globals *Globals::m_instance=nullptr;

Globals::Globals()
{

}
/*
* 函数名：getInstance
* 参数：无
* 返回：Globals*
* 功能：返回单例
*/
Globals* Globals::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new Globals();
    }
    return m_instance;
}
/*
* 函数名：Logging
* 参数：QString
* 返回：无
* 功能：日志生成
*/
void Globals::Logging(QString data)
{
    QFile file("log.txt");
    if (!file.open(QIODevice::Append))
        qDebug() << "Cannot open file for appending";
    file.write(data.toLatin1());
    file.close();
}
/*
* 函数名：GetSysTime
* 参数：无
* 返回：QString
* 功能：返回系统时间，格式：yyyy-mm-dd hh:mm:ss.zzz
*/
QString Globals::GetSysTime()
{
    QDateTime ctime=QDateTime::currentDateTime();
    QString current_time=ctime.toString("yyyy-MM-dd hh:mm:ss.zzz");
    return current_time;
}
/*
* 函数名：GetRandomData
* 参数：int
* 返回：int
* 功能：返回一个定义范围的随机整数
*/
int Globals::GetRandomData(int max)
{

}
