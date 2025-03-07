#ifndef STRUCTDEF_H
#define STRUCTDEF_H

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
#include <QLibrary>
#include <QDebug>
#include <dlfcn.h>
#include <iostream>
#include <sstream>
#include <QRandomGenerator>
/*
 * 宏定义头文件
 */
using namespace std;

#define ARRAYMAX 1024       //基础字节数
//子系统模块ID
#define SYSDATA 0
#define DPLC 1
#define DATAB 2
#define PM 3
#define DMM 4
#define QM 5
#define MM 6
#define RM 7
#define EXTIF 8
#define IMP 9
#define RPT 10
#define SWP01 101
#define CTI01 102

//IO配置文件
struct IOConfig_IO_addition
{
    QString name;
    QString type;
};

struct IOConfig_IO_io
{
    QString name;
    QString id;
};

struct IOConfig_IO
{
    uint8_t type;
    QString name;
    QString addr;
    QString desc;
    QList<IOConfig_IO_io> input;
    QList<IOConfig_IO_io> output;
    QList<IOConfig_IO_addition> addtion;
};

struct IOConfig
{
    QString ip;
    uint16_t port;
    QString socket;
    uint16_t sport;
    QString sn;
    QList<IOConfig_IO> IO;
};
//模块列表类及其成员类
struct Module_TwoD_Node_Info_Knobpair_Guid
{
    QString self;
    QString other;
};

struct Module_TwoD_Node_Info_Knobpair
{
    QString name;
    uint8_t id;
    uint8_t io;
    Module_TwoD_Node_Info_Knobpair_Guid guid;
};

struct Module_TwoD_Node_Info
{
    QString guid;
    QString name;
    uint8_t type;
    QString length;
    QString addr;
    QString refresh;
    QString desc;
    QString bindaddr;
    QList<Module_TwoD_Node_Info_Knobpair> knobpair;     //节点列表
};

struct Module_TwoD_Node
{
    Module_TwoD_Node_Info info;
};

struct Module_TwoD
{
    Module_TwoD_Node node;
};

struct Module
{
    QString group;
    QString name;
    QList<Module_TwoD> twod;
};
//注册变量单元
struct VarUnit
{
    uint16_t sysid;         //子系统ID
    QString idname;         //变量ID
    char type;              //变量类型  I(DI)、O(DO)、i(AI)、o(AO)、F(F)、N(N)、M(M)
    uint32_t idaddr;        //变量值存储点位(唯一),用6位十进制数表示,内存空间位置需由变量类型共同决定
                            //如DIDO类型值为000800则表示第801个点位，内存地址为0x0064上的bit0;
                            //如AIAO类型值为000800则表示第801个点位，内存地址为0x0100～0x0101两个字节
    //uint16_t readdr;      //变量寄存器地址(硬件地址)
    uint32_t length;        //数据长度，单位：字节
    QString desc;           //变量描述，纯文本字符串
    QString init_value;     //初始值
    size_t fresh=0;         //刷新周期，单位:ms，默认为0时不刷新数据
};
//ID分解
struct Var_ID_Type
{
    uint32_t id32;
    uint16_t type;
};
//变量注册输入成员
struct sRegisterVarPar
{
    QString idname;     //变量ID助记符
    uint16_t type;       //变量类型
    uint32_t length;    //数据长度，单位：字节
    QString description;//数据说明
};
//变量注册返回成员
struct sRegisterVarRet
{
    QString id;        //变量ID
    uint16_t addr;      //变量地址
    uint32_t length;    //变量长度，单位：字节
    char code;          //错误码   0：成功，<0失败
};
//读变量输入成员
struct sReadVarPar
{
    char type;
    uint32_t addr;      //起始地址
    uint32_t length;    //变量长度，单位：点位
    uint32_t num;       //变量数量
};
//读变量返回成员
struct sReadVarRet
{
    char type;
    uint32_t addr;      //起始地址
    vector<uint8_t> value;             //变量值
    uint32_t length;            //变量长度，单位：字节
    uint16_t num;       //变量数量
};
//读内存输入成员
struct sReadMPar
{
    uint16_t addr;      //内存起始地址
    uint32_t length;    //内存读取长度
};
//读内存返回成员
struct sReadMRet
{
    uint32_t length;                //读取长度
    vector<unsigned char> value;    //读取值数组
};
//写内存输入成员
struct sWriteMPar
{
    uint32_t length;                //写入长度
    uint16_t addr;                  //写入起始地址
    vector<unsigned char> value;    //写入数据
};
//写内存返回成员
struct sWriteMRet
{
    uint32_t length;    //写入长度
    char code;          //写入结果
};
//写变量输入成员
struct sWriteVarPar
{
    char type;
    uint16_t addr;              //变量地址
    vector<uint8_t> value;     //变量值
    uint32_t length;            //变量长度，单位：字节
};
//写变量返回成员
struct sWriteVarRet
{
    char type;
    uint16_t addr;        //变量地址
    char code;          //错误码   0：成功，<0失败
};
//传输变量输入成员
struct sTransferVarPar
{
    char type;                  //变量类型
    uint16_t addr;              //变量地址
    uint32_t length;            //数据长度，单位：字节
    vector<uint16_t> value;     //变量值
};
//传输变量返回成员
struct sTransferVarRet
{
    QString id;        //变量ID
    uint32_t length;    //数据长度，单位：字节
    char code;          //错误码   0：成功，<0失败
};
//采集变量输入成员
struct sScanVarPar
{
    QString id;        //变量ID
    uint32_t length;    //数据长度，单位：字节
};
//采集变量返回成员
struct sScanVarRet
{
    QString id;        //变量ID
    uint32_t length;    //数据长度，单位：字节
    uint32_t data;      //数据
    char code;          //错误码   0：成功，<0失败
};

#endif // STRUCTDEF_H
