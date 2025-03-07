#ifndef HANDLESYSDATA_H
#define HANDLESYSDATA_H

#include <mutex>
#include <QThread>
#include <QObject>
#include "Globals/globals.h"

using namespace std;
/*
 * 数据处理线程类，系统数据中心集中管理方法
 */
class HandleSysData : public QThread
{
    Q_OBJECT
public:
    static HandleSysData* getInstance();

    void run() override;
//两类数据处理，一类寄存器存储，一类系统变量存储
    void Process_ScanData();

    void Process_TransData();

    void Process_ChangeData();

    void Process_WriteData();

    void Process_ReadData();

private:
    //私有化构造函数和析构函数
    HandleSysData();
    ~HandleSysData();
    HandleSysData(const HandleSysData&) = delete;
    HandleSysData& operator=(const HandleSysData&) = delete;
    //静态成员变量保存唯一实例
    static HandleSysData* m_instance;
    //采传读写唯一互斥锁
    static mutex m_mtx;
    //线程退出标志位
    bool m_quit_flag;
    //写数据BUF
};

#endif // HANDLESYSDATA_H
