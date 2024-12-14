#ifndef GLOBALS_H
#define GLOBALS_H

#include <mutex>
#include <QString>
#include <iostream>
#include <fstream>
#include <ctime>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QRandomGenerator>

//数据库类型
enum SystemDataType
{
    ST_Device,
    ST_DataRt,
    ST_DataHis,
    ST_DataRec,
    ST_Sheet,
    ST_SheetField,
    ST_SheetData,
    ST_Users,
    ST_Roles,
    ST_Operation,
    ST_Manager,
    ST_Department,
    ST_Group,
    ST_OpLog,
    ST_AlLog,
    ST_SysLog,
};

class Globals {
public:
    static Globals* getInstance();

    //日志文件
    void Logging(QString data);
    QString GetSysTime();
    int GetRandomData(int max);
private:
    //私有化构造函数和析构函数
    Globals();
    ~Globals();
    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;
    //静态成员变量保存唯一实例
    static Globals* m_instance;
    static std::mutex mutex;
    //全局变量
};

#endif // GLOBALS_H
