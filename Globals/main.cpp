#include "mainwindow.h"
#include "Alarm/alarm.h"
#include "DPLCExt/dplcserver.h"
#include "Datasystem/tcpserver.h"
#include "Datasystem/mytcpsocket.h"
#include "Filesystem/fileserver.h"
#include "Datasystem/serialportserver.h"
#include "threadtimer.h"
#include <QApplication>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //初始化各通讯端口
    Tcpserver::getInstance()->listen(QHostAddress::Any,9527);
    FileServer::getInstance()->listen(QHostAddress::Any,9999);
    // QStringList serialportlist=SerialPortServer::getInstance().GetAllComList();
    // for(auto item:serialportlist)           //连接所有端口
    // {
    //     SerialPortServer::getInstance().AddSerialPort(item);    //此处添加了所有串口至设备列表，但无法通过指令查询到串口对应设备和型号
    // }
    //读取JSON文件
    JsonFile::getInstance()->ReadJsonFile("ioconfig.json");
    //初始化控制模块
    DPLCServer::getInstance()->moveToThread(DPLCServer::getInstance()->m_thread);
    //初始化报警模块
    Alarm::getInstance()->moveToThread(Alarm::getInstance()->m_alarm_thread);
    Alarm::getInstance()->m_alarm_thread->start();
    //时钟线程
    ThreadTimer threadtimer;
    threadtimer.start();
#ifdef TEST
    MainWindow w;
    w.show();
#endif
    a.exec();
}
