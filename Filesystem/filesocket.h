#ifndef FILESOCKET_H
#define FILESOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <chrono>
#include <QTimer>
#include <QFile>
#include "filesocket.h"
#include <QCoreApplication>
#include <QDir>
#include <QTime>
#include <QBuffer>
#include <QDataStream>

#include "Globals/globals.h"
#include "DPLCExt/dplcserver.h"

class FileSocket : public QObject
{
    Q_OBJECT
public:
    explicit FileSocket(QObject *parent = nullptr);
    ~FileSocket();

    FileSocket *m_this_point;
    QTcpSocket *m_socket;
public slots:
    void onReceiveJsonFile();
    void Init();
private:
    QByteArray m_revbuf;
    uint16_t m_sysid;
};

#endif // FILESOCKET_H
