#ifndef DPLCCC_H
#define DPLCCC_H
#include "DPLCExt/dplcextbase.h"
/*
 * 流程控制模块
 * 固定节点
 */
//IN:
//m_nodein_list[0]:RESET
//m_nodein_list[1]:TRIGGER
//m_nodein_list[2]:OVER
//OUT:
//m_nodeout_list[0]:RST
//m_nodeout_list[1]:DO
//m_nodeout_list[2]:NEXT
class DPLCCC:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCCC_H
