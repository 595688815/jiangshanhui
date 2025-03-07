#include "dplcor.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCor::OnRun()
{
    if(m_nodein_list.size()<2 || m_nodeout_list.size()!=1)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    for(auto item:m_nodein_list)
    {
        SetValWrite(item,(uint8_t)0);
    }
    for(auto item:m_nodeout_list)
    {
        SetValWrite(item,(uint8_t)0);
    }
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCor::Run()
{
    if(!CheckClassFlag("OR模块节点非法"))
        return false;
    for(auto item:m_nodein_list)
    {
        if(NodeValueToD(item)==1)
        {
            #ifdef TEST
            qDebug()<<"输入信号存在置1";
            qDebug()<<"Or模块触发";
            qDebug()<<"输出置1";
            #endif
            if(!SetValWrite(m_nodeout_list[0],(uint8_t)1))
            {
                qDebug()<<"或模块输出变量写入失败";
                Globals::getInstance()->Logging("或模块输出变量写入失败");
            }
            //复位
            for(auto item:m_nodein_list)
            {
                #ifdef TEST
                qDebug()<<"输入信号复位";
                #endif
                if(!SetValWrite(item,(uint8_t)0))
                {
                    qDebug()<<"或模块输出变量写入失败";
                    Globals::getInstance()->Logging("或模块输出变量写入失败");
                }
            }
            return true;
        }
    }
    return true;
}
