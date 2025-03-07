#ifndef DPLCEXTBASE_H
#define DPLCEXTBASE_H
/*
 * DPLC拓展模块基类
 */
#include "DPLCExt/dplcackbase.h"

class DPLCExtBase:public DPLCBase
{
public:
    using DPLCBase::DPLCBase;
    DPLCAckBase *p_ack;         //回迅模块指针
signals:
    void InforAckBack();
};

#endif // DPLCEXTBASE_H
