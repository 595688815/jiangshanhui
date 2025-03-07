#ifndef DPLCSS_H
#define DPLCSS_H
#include "DPLCExt/dplcackbase.h"
/*
 * 单路回讯模块
 */
//IN:
//m_nodein_list[0]:In
//OUT:
//m_nodeout_list[0]:ACK
class DPLCSS:public DPLCAckBase
{
public:
    using DPLCAckBase::DPLCAckBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCSS_H
