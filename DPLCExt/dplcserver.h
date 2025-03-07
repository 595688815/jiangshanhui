#ifndef DPLCSERVER_H
#define DPLCSERVER_H
/*
 * 此类用于管理DPLC所有模块
 */
#include <QMap>
#include <QList>
#include <QFile>
#include <thread>
#include <chrono>
#include <QThread>
#include <QObject>
#include "Filesystem/jsonfile.h"
#include "DPLCExt/dplcai.h"
#include "DPLCExt/dplcao.h"
#include "DPLCExt/dplcdi.h"
#include "DPLCExt/dplcdo.h"
#include "DPLCExt/dplcf.h"
#include "DPLCExt/dplcm.h"
#include "DPLCExt/dplcn.h"
#include "DPLCExt/dplcact.h"
#include "DPLCExt/dplcand.h"
#include "DPLCExt/dplcbranch.h"
#include "DPLCExt/dplccc.h"
#include "DPLCExt/dplcdc.h"
#include "DPLCExt/dplcds.h"
#include "DPLCExt/dplcnot.h"
#include "DPLCExt/dplcor.h"
#include "DPLCExt/dplcpc.h"
#include "DPLCExt/dplcpw.h"
#include "DPLCExt/dplccw.h"
#include "DPLCExt/dplcreset.h"
#include "DPLCExt/dplcsc.h"
#include "DPLCExt/dplcss.h"
#include "DPLCExt/dplcvcc.h"
#include "DPLCExt/dplctrigger.h"
using namespace std;

class DPLCServer : public QThread
{
public:
    friend class DPLCExtBase;
    static DPLCServer* getInstance();
    QThread *m_thread;

    void Init();
    void RefreshDPLCConnect();
    void ThreadStart();
    void ThreadStop(){m_thread_flag=false;}
    void run() override;
    void quit();
private:
    //私有化构造函数和析构函数
    DPLCServer();
    ~DPLCServer();
    DPLCServer(const DPLCServer&) = delete;
    DPLCServer& operator=(const DPLCServer&) = delete;

    QList<DPLCBase*> p_dplc_extlist;     //外置拓展模块链表
    //静态成员变量保存唯一实例
    static DPLCServer* m_instance;
    DPLCVCC *p_vcc=nullptr;             //VCC全局唯一
    DPLCRESET *p_reset=nullptr;         //RESET全局唯一
    bool m_thread_flag;                 //线程标志位
};

#endif // DPLCSERVER_H
