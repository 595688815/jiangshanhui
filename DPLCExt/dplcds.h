#ifndef DPLCDS_H
#define DPLCDS_H
#include "DPLCExt/dplcackbase.h"
/*
 * 双路回讯模块
 */
//IN:
//m_nodein_list[0]:In1
//m_nodein_list[1]:In2
//OUT:
//m_nodeout_list[0]:out
class DPLCDS:public DPLCAckBase
{
public:
    using DPLCAckBase::DPLCAckBase;

    bool Run() override;
    bool OnRun() override;
private:
    uint8_t m_V1;   //输出为1时In1的有效值
    uint8_t m_V2;   //输出为1时In2的有效值
};

#endif // DPLCDS_H
