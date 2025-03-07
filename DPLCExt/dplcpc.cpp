#include "dplcpc.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCPC::OnRun()
{
    if(m_nodein_list.size()<3 || m_nodeout_list.size()<3)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCPC::Run()
{
    if(!CheckClassFlag("PC模块节点非法"))
        return false;
    if(NodeValueToD(m_nodein_list[0])==1)
    {
        //输入参数列表
        QList<QByteArray> param_in_list;
        for(int i=1;i<m_nodein_list.size()-1;++i)
            param_in_list.append(NodeValueToM(m_nodein_list[i]));
        //参数运算
        QList<QByteArray> param_out_list;
        //输出参数列表
        for(int i=1;i<m_nodeout_list.size()-1;++i)
            SetValWrite(m_nodeout_list[i],(QByteArray)(param_out_list[i]));
        SetValWrite(m_nodeout_list[0],(uint8_t)(1));
    }
    return true;
}
