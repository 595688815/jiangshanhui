#ifndef JSONFILE_H
#define JSONFILE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <iostream>
#include <QList>
#include "Globals/globals.h"
#include "Datasystem/tcpserver.h"
/*
* DPLC类Json文件结构,QT6->QT5
*/
class JsonFile
{
public:
    JsonFile();
    static JsonFile* getInstance();
    bool ReadJsonFile(QString filePath);
    QByteArray VarToJsonByteArray();
    void VarToJsonFile();
    void VarToJsonFile(MyTcpSocket *socket);
private:
    //静态成员变量保存唯一实例
    static JsonFile* m_instance;
    QJsonObject m_jsonobject;
};
#endif // JSONFILE_H
