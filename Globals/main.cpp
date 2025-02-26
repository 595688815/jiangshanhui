#include "mainwindow.h"
#include "Datasystem/tcpserver.h"
#include "Datasystem/mytcpsocket.h"
#include "Filesystem/fileserver.h"
#include "Datasystem/serialportserver.h"
#include <QApplication>

#define TEST

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SystemSql::getInstance()->InitFromMysql();
    Tcpserver::getInstance().listen(QHostAddress::Any,9527);
    FileServer2::getInstance().listen(QHostAddress::Any,9999);
    QStringList serialportlist=SerialPortServer::getInstance().GetAllComList();
    for(auto item:serialportlist)           //连接所有端口
    {
        SerialPortServer::getInstance().AddSerialPort(item);    //此处添加了所有串口至设备列表，但无法通过指令查询到串口对应设备和型号

    }
#ifdef TEST
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
