#ifndef GLOBALS_H
#define GLOBALS_H

#include <mutex>
#include <vector>
#include <QList>
#include <QString>
#include <iostream>
#include <fstream>
#include <ctime>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QRandomGenerator>

#define ARRAYMAX 1024       //基础字节数
//7种数据类型模板
#define TYPE_DI 1
#define TYPE_DO 2
#define TYPE_AI 3
#define TYPE_AO 4
#define TYPE_N 5
#define TYPE_F 6
#define TYPE_LL 7
#define TYPE_M0 7   //8-7表示占用1个字节的M型变量
//#define TYPE_M1 8
//#define TYPE_M2 9

using namespace std;

static mutex m_serialport_mtx;      //串口通讯锁
static mutex m_socket_mtx;          //网口通讯锁
static mutex m_variable_mtx;        //变量操作锁
static mutex m_mysql_mtx;           //数据库操作锁

class Globals {
public:
    static Globals* getInstance();
    //变量注册接口
    int m_array_ext;    //扩展的容量
    int m_user_define_addr_begin;
    vector<unsigned char> m_var_value_array;
    vector<unsigned char> m_var_status_array;
    struct VarRegisterClass
    {
        uint32_t modulID;       //模块ID
        uint32_t varID;         //变量ID
        uint32_t type;          //数据类型
        uint32_t fretime;       //刷新周期
        uint16_t soft_addr;     //变量计算机地址
        uint16_t regi_addr;     //寄存器地址
        bool operator==(const VarRegisterClass& t) {
            return (modulID == t.modulID) && (varID == t.varID) && (type == t.type) && (fretime == t.fretime) && (soft_addr == t.soft_addr) && (regi_addr == t.regi_addr);
        }
    };
    QList<VarRegisterClass> m_var_register_list;
    //日志文件
    void Logging(QString data);
    //Test
    QString GetSysTime();
    int GetRandomData(int max);
    //CRC校验处理方法
    unsigned short getCRC(char* buf, int length);
    //变量注册方法
    uint32_t RegisterVar(uint32_t modulID,uint32_t varID, uint32_t type,uint32_t freshtime,uint16_t addr);
    //变量注销方法
    uint32_t LogOffVar(VarRegisterClass var);
    //扩展变量注册链表
    uint32_t ExtVarList(uint32_t num);
private:
    //私有化构造函数和析构函数
    Globals();
    ~Globals();
    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;
    //静态成员变量保存唯一实例
    static Globals* m_instance;
    //全局变量
};

#endif // GLOBALS_H
