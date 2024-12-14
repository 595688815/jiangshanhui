#include "mainwindow.h"
#include "tcpserver.h"
#include "mytcpsocket.h"
#include "fileserver2.h"
#include <QApplication>

#define TEST

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tcpserver::getInstance().listen(QHostAddress::Any,56666);
    FileServer2::getInstance().listen(QHostAddress::Any,9999);
#ifdef TEST
    MainWindow w;
    w.show();
#endif
    return a.exec();
}
