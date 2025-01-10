#include "modbustcpclient.h"

ModbusTcpClient *ModbusTcpClient::instance = nullptr;

ModbusTcpClient::ModbusTcpClient(QObject *parent) : QObject(parent), modbusContext(nullptr)
{
    //    infoBox = nullptr;
}

ModbusTcpClient::~ModbusTcpClient()
{
    if(modbusContext)
    {
        modbus_free(modbusContext);
        modbusContext = nullptr;
    }
    disconnect();
}
/*
 * 函数名：connectToServer
 * 参数：const QString,int
 * 返回：bool
 * 函数说明：连接至服务器
*/
bool ModbusTcpClient::connectToServer(const QString &serverIP, int port)
{
    static bool errorDisplayed = false;
    static bool errorShown = false; // 静态标志

    m_serverIP = serverIP;
    m_port = port;
    if(modbusContext != nullptr)
    {
        modbus_free(modbusContext);
        modbusContext = nullptr;
    }
    modbusContext = modbus_new_tcp(serverIP.toStdString().c_str(), port);
    if(modbusContext == nullptr)
    {
        if(!errorDisplayed)
        {
            if(!errorShown)
            {
                errorShown = true;
            }
            errorDisplayed = true;
        }
        return false;
    }

    if(modbus_connect(modbusContext) == -1)
    {
        if(!errorDisplayed)
        {
            if(!errorShown)
            {
                errorShown = true;
            }
            errorDisplayed = true;
        }
        modbus_free(modbusContext);
        modbusContext = nullptr;
        return false;
    }
    errorDisplayed = false;
    errorShown = false;
    return true;
}
/*
 * 函数名：disconnect
 * 参数：无
 * 返回：无
 * 函数说明：断开连接
*/
void ModbusTcpClient::disconnect()
{
    if(modbusContext != nullptr)
    {
        modbus_close(modbusContext);
        modbus_free(modbusContext);
        modbusContext = nullptr;
    }
}
/*
 * 函数名：isConnected
 * 参数：无
 * 返回：bool
 * 函数说明：获取连接状态字
*/
bool ModbusTcpClient::isConnected()const
{
    return m_isConnected;
}
/*
 * 函数名：reconnect
 * 参数：无
 * 返回：无
 * 函数说明：重新连接
*/
void ModbusTcpClient::reconnect()
{
    disconnect();
    connectToServer(m_serverIP, m_port);
}
