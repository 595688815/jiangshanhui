#include "dplcreset.h"
/*
* 函数名：OnRun
* 参数：无
* 返回：bool
* 功能：初始化函数
*/
bool DPLCRESET::OnRun()
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
        node.var.idaddr=6;
        node.p_id="RESET";
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
    return true;
}
/*
* 函数名：Run
* 参数：无
* 返回：bool
* 功能：运行函数
*/
bool DPLCRESET::Run()
{
    if(!CheckClassFlag("RESET模块节点非法"))
        return false;
    return true;
}

