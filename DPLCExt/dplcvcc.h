#ifndef DPLCVCC_H
#define DPLCVCC_H
#include "DPLCExt/dplcextbase.h"
/*
 * 系统电源模块
 */
//OUT:
//m_nodeout_list[0]:out
class DPLCVCC:public DPLCExtBase
{
public:
    using DPLCExtBase::DPLCExtBase;

    bool Run() override;
    bool OnRun() override;
};

#endif // DPLCVCC_H
