#ifndef GLOBALS_H
#define GLOBALS_H

#define TEST

#include <QFileInfo>
#include "Globals/structdef.h"
#include "Datasystem/mytcpsocket.h"

static mutex m_serialport_mtx;      //串口通讯锁
static mutex m_socket_mtx;          //网口通讯锁
static mutex m_variable_mtx;        //变量操作锁
static mutex m_mysql_mtx;           //数据库操作锁

class Globals {
public:
    static Globals* getInstance();
    //日志文件
    void Logging(QString data);
    void DebugText(QString texg);
    //Test
    QString GetSysTime();
    int GetRandomData(int max);
    //CRC校验处理方法
    uint16_t getCRC(char* buf, int length);
    //变量注册接口
    int m_array_ext;    //扩展的容量
    int m_user_define_addr_begin;
    vector<uint8_t> m_var_value_array;
    vector<uint8_t> m_var_status_array;
    //子系统注册接口函数
    int RegisterModule(uint16_t subsysid,uint16_t subsystype);
    //变量操作接口
    sReadVarRet ReadVar(sReadVarPar var);
    sReadVarRet ReadVar(VarUnit var);
    sWriteVarRet WriteVar(sWriteVarPar var);
    sReadMRet ReadM(sReadMPar var);
    sWriteMRet WriteM(sWriteMPar var);
    sTransferVarRet TransferVar(sTransferVarPar var,MyTcpSocket *pTcpSocket);
    sScanVarRet ScanVar(sScanVarPar var);
    //变量直接获取接口
    uint8_t GetValueToD(VarUnit var);
    uint16_t GetValueToA(VarUnit var);
    float GetValueToF(VarUnit var);
    uint32_t GetValueToN(VarUnit var);
    QByteArray GetValueToM(VarUnit var);
    //
    uint32_t AddSendBuf(QByteArray msg);
    //注册变量链表操作接口
    int AddVarUnit(VarUnit var);
    int ChangeVarUint(VarUnit var);
    int DeleteVarUint(VarUnit addr);
    int GetVarUnit(VarUnit &var,uint32_t addr);
    uint32_t GetVarListSize();
    int RegisterAddr(uint32_t &addr,char type,uint32_t length);
    int RegisterVar(uint32_t addr,char type,uint32_t length,QString valueq);

    bool RenameCheck(QString idname);

    QList<VarUnit> GetVarList(){return m_var_list;}

    QList<Module> *GetModuleList(){return &m_module_list;}
    QList<Module> *GetStationList(){return &m_station_list;}
    IOConfig *GetIOConfig(){return &m_ioconfig;}

    char GetVarType(uint8_t varid,uint8_t id,uint8_t io);

    uint8_t GetAlarmStatus(){return m_alarm_flag;}
    void SetAlarmStatus(uint8_t value){m_alarm_flag=value;}     //报警信号设置，任何类可访问，一旦报警程序会进入报警状态，严重报警会停止程序且需要清除报警标志才能继续运行程序

    QList<QPair<uint8_t,QString>> *GetAlarmList(){return &m_alarm_list;}

    uint8_t GetStationNum(){return m_station_num;}
    void SetStationNum(uint8_t value){m_station_num=value;}
private:
    //私有化构造函数和析构函数
    Globals();
    ~Globals();
    Globals(const Globals&) = delete;
    Globals& operator=(const Globals&) = delete;
    //静态成员变量保存唯一实例
    static Globals* m_instance;
    //读硬件空间缓存BUF
    QList<sReadMRet> m_readm_buff_list;
    //写硬件空间缓存BUF
    QList<sWriteMRet> m_writem_buff_list;
    //注册变量链表，无序链表
    QList<VarUnit> m_var_list;
    //模组链表
    QList<Module> m_module_list;
    //工位链表
    QList<Module> m_station_list;
    //IO配置文件
    IOConfig m_ioconfig;
    //报警标志位
    uint8_t m_alarm_flag=0;
    QList<QPair<uint8_t,QString>> m_alarm_list;
    //当前工位号
    uint8_t m_station_num;
    //全局变量
};

#endif // GLOBALS_H
