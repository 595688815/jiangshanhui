#ifndef DPLCACKBASE_H
#define DPLCACKBASE_H
#include "DPLCExt/dplcbase.h"
/*
 * DPLC回迅模块基类
 */
class DPLCAckBase : public DPLCBase
{
public:
    using DPLCBase::DPLCBase;

    uint8_t ReturnACKStatus(){return m_ack_status;}
    void SetACKStatus(uint8_t value){m_ack_status=value;}
private:
    uint8_t m_ack_status;   //回迅状态
};

#endif // DPLCACKBASE_H
