#ifndef MODBUSTCPCLIENT_H
#define MODBUSTCPCLIENT_H

#include <QObject>
#include <QString>
#include <QMutex>
#include <modbus/modbus.h>
/*
 *
 */

class ModbusTcpClient : public QObject
{
    Q_OBJECT
public:
    ModbusTcpClient(QObject *parent = nullptr);
    static ModbusTcpClient *getInstance(); // 获取单例实例的静态方法
    ~ModbusTcpClient();

    bool connectToServer(const QString &serverIP, int port); // 连接
    void disconnect(); // 断开
    bool isConnected() const;  // 判断是否已连接到服务器
    void reconnect();  // 重新连接到Modbus服务器
private:
    static ModbusTcpClient *instance; // 单例实例静态成员变量

    modbus_t *modbusContext;
    QString m_serverIP;
    int m_port;
    bool m_isConnected = false;
};

#endif // MODBUSTCPCLIENT_H
