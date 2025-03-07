#include "dplcvcc.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数,程序运行前先置1
*/
bool DPLCVCC::OnRun()
{
    if(m_nodeout_list.size()!=1)
    {
        m_class_creat_flag=false;
        return false;
    }
    else
        m_class_creat_flag=true;
    if(m_nodeout_list.isEmpty())
    {
        Node node;
        node.var.idaddr=7;
        node.p_id="VCC";
        node.var.type='O';
        for(auto item:Globals::getInstance()->GetVarList())
        {
            if(item.type==node.var.type && item.idaddr==node.var.idaddr)
            {
                node.var=item;
            }
        }
        m_nodeout_list.push_back(node);
    }
    SetValWrite(m_nodeout_list[0],(uint8_t)1);
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCVCC::Run()
{
    if(!CheckClassFlag("VCC模块节点非法"))
        return false;
    return true;
}
