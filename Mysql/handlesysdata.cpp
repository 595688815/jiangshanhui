#include "Mysql/handlesysdata.h"

HandleSysData *HandleSysData::m_instance=nullptr;

HandleSysData::HandleSysData()
{
    m_quit_flag=false;
}

HandleSysData::~HandleSysData()
{
    m_quit_flag=true;
}
/*
* 函数名：getInstance
* 参数：无
* 返回：HandleSysData*
* 功能：返回单例
*/
HandleSysData* HandleSysData::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new HandleSysData();
    }
    return m_instance;
}
/*
* 函数名：run
* 参数：无
* 返回：无
* 功能：线程运行函数
*/
void HandleSysData::run()
{
    while(!m_quit_flag)
    {

    }
}
/*
* 函数名：Process_ChangeData
* 参数：无
* 返回：无
* 功能：数据改变过程
*/
void HandleSysData::Process_ChangeData()
{

}
/*
* 函数名：Process_ScanData
* 参数：无
* 返回：无
* 功能：数据扫描过程
*/
void HandleSysData::Process_ScanData()
{

}
/*
* 函数名：Process_TransData
* 参数：无
* 返回：无
* 功能：数据传输过程
*/
void HandleSysData::Process_TransData()
{

}
/*
* 函数名：Process_WriteData
* 参数：无
* 返回：无
* 功能：数据写入过程
*/
void HandleSysData::Process_WriteData()
{

}
/*
* 函数名：Process_ReadData
* 参数：无
* 返回：无
* 功能：数据读取过程
*/
void HandleSysData::Process_ReadData()
{

}
