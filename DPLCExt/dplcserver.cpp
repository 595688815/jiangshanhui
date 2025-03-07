#include "dplcserver.h"

DPLCServer *DPLCServer::m_instance=nullptr;

DPLCServer::DPLCServer()
{
    m_thread_flag=true;
    m_thread=new QThread;
    connect(m_thread,&QThread::started,this,&DPLCServer::run);
    Init();
}

DPLCServer::~DPLCServer()
{
    m_thread->quit();
    m_thread->wait();
    m_thread->deleteLater();
}
/*
* 函数名：quit
* 参数：无
* 返回：无
* 功能：退出线程
*/
void DPLCServer::quit()
{
    m_thread_flag=false;
}
/*
* 函数名：getInstance
* 参数：无
* 返回：DPLCServer*
* 功能：返回单例
*/
DPLCServer* DPLCServer::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new DPLCServer();
    }
    return m_instance;
}
/*
* 函数名：Init
* 参数：无
* 返回：无
* 功能：初始化DPLC管理服务，读取配置文件内置变量实例化
*/
void DPLCServer::Init()
{
    //内置变量模块
    QFile file("ddms.sys");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file for sending.";
        return;
    }
    uint32_t type=0;
    while(!file.atEnd())
    {
        QByteArray str=file.readLine();
        if(str.startsWith("//"))    //注释行直接跳过
            continue;
        //筛除干扰字符串
        str.replace("\n","");
        str.replace(";","");

        if(str.startsWith("@DI"))
        {
            type='I';
        }
        if(str.startsWith("@DO"))
        {
            type='O';
        }
        if(str.startsWith("@AI"))
        {
            type='i';
        }
        if(str.startsWith("@AO"))
        {
            type='o';
        }
        if(str.startsWith("@N"))
        {
            type='N';
        }
        if(str.startsWith("@F"))
        {
            type='F';
        }
        if(str.startsWith("@M"))
        {
            type='M';
        }
        QList<QByteArray> strlist=str.split(',');
        if(strlist.size()<3)    //筛除无效行
            continue;

        switch (type) {
        case 'I':
        case 'O':
        {
            VarUnit varunit;
            varunit.idname=strlist[0];
            varunit.type=type;
            varunit.length=1;
            varunit.sysid=0;
            varunit.idaddr=strlist[1].toUInt();
            varunit.init_value=strlist[2];
            sWriteVarPar var;
            var.addr=varunit.idaddr;
            var.length=varunit.length;
            var.type=varunit.type;
            var.value.push_back(varunit.init_value.toInt()&0x01);
            Globals::getInstance()->WriteVar(var);
            Globals::getInstance()->AddVarUnit(varunit);
        }
            break;

        case 'i':
        case 'o':
        {
            VarUnit varunit;
            varunit.idname=strlist[0];
            varunit.type=type;
            varunit.length=2;
            varunit.sysid=0;
            varunit.idaddr=strlist[1].toUInt();
            varunit.init_value=strlist[2];
            sWriteVarPar var;
            var.addr=varunit.idaddr;
            var.length=varunit.length;
            var.type=varunit.type;
            uint8_t ch[2];
            ch[0]=((varunit.init_value.toUInt()>>8)&0xff);
            ch[1]=(varunit.init_value.toUInt()&0xff);
            var.value.push_back(ch[0]);
            var.value.push_back(ch[1]);
            Globals::getInstance()->WriteVar(var);
            Globals::getInstance()->AddVarUnit(varunit);
        }
        break;

        case 'N':
        case 'F':
        {
            VarUnit varunit;
            varunit.idname=strlist[0];
            varunit.type=type;
            varunit.length=4;
            varunit.sysid=0;
            varunit.idaddr=strlist[1].toUInt();
            varunit.init_value=strlist[2];
            sWriteVarPar var;
            var.addr=varunit.idaddr;
            var.length=varunit.length;
            var.type=varunit.type;
            uint8_t ch[4];
            if(type=='N')
            {
                ch[0]=((varunit.init_value.toUInt()>>24)&0xff);
                ch[1]=((varunit.init_value.toUInt()>>16)&0xff);
                ch[2]=((varunit.init_value.toUInt()>>8)&0xff);
                ch[3]=(varunit.init_value.toUInt()&0xff);
            }
            if(type=='F')
            {
                float f=varunit.init_value.toFloat();
                memcpy(ch,&f,sizeof(f));
            }
            for(int i=0;i<4;++i)
                var.value.push_back(ch[i]);
            Globals::getInstance()->WriteVar(var);
            Globals::getInstance()->AddVarUnit(varunit);
        }
        break;

        case 'M':
        {
            if(strlist.size()>3)
            {
                VarUnit varunit;
                varunit.idname=strlist[0];
                varunit.type=type;
                varunit.length=strlist[1].toUInt();
                varunit.sysid=0;
                varunit.idaddr=strlist[2].toUInt();
                varunit.init_value=strlist[3];
                sWriteVarPar var;
                var.addr=varunit.idaddr;
                var.length=varunit.length;
                var.type=varunit.type;
                for(auto item:varunit.init_value.toLatin1())
                    var.value.push_back(item);
                Globals::getInstance()->WriteVar(var);
                Globals::getInstance()->AddVarUnit(varunit);
            }
        }
            break;
        }
    }

    //唯一VCC、RESET
    p_vcc =new DPLCVCC("VCC","",'I',"VCC");
    for(auto var_unit:Globals::getInstance()->GetVarList())
    {
        if("VCC"==var_unit.idname)   //匹配成功
        {
            DPLCExtBase::Node node;
            node.var=var_unit;
            p_vcc->m_nodeout_list.push_back(node);
        }
    }
    p_reset =new DPLCRESET("RESET","",'O',"RESET");
    for(auto var_unit:Globals::getInstance()->GetVarList())
    {
        if("RESET"==var_unit.idname)   //匹配成功
        {
            DPLCExtBase::Node node;
            node.var=var_unit;
            p_reset->m_nodeout_list.push_back(node);
        }
    }
}
/*
* 函数名：RefreshDPLCConnect
* 参数：无
* 返回：无
* 功能：刷新DPLC模块连接状态，根据JSON文件配置完所有DPLC模块
*/
void DPLCServer::RefreshDPLCConnect()
{
    // //清空DPLC模块
    qDeleteAll(p_dplc_extlist);
    p_dplc_extlist.clear();
    //重新部署DPLC模块
    QList<Module> modlist=*Globals::getInstance()->GetStationList();
    for(auto pro_unit:modlist)
    {
        for(auto mod_unit:pro_unit.twod)
        {
            switch (mod_unit.node.info.type) {
            case 1:
            {
                DPLCBase *dplcbase=new DPLCDI(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=1;
                    node.var.type='O';
                    //绑定触发变量
                    if(!mod_unit.node.info.bindaddr.isEmpty())
                    {
                        for(auto item:Globals::getInstance()->GetVarList())
                        {
                            if(item.idname==mod_unit.node.info.bindaddr)
                            {
                                node.bind_flag=true;
                                dplcbase->m_bind_var=item;
                                break;
                            }
                        }
                    }
                    dplcbase->m_nodeout_list.push_back(node);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 2:
            {
                DPLCBase *dplcbase=new DPLCDO(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=1;
                    node.var.type='I';
                    //绑定触发变量
                    if(!mod_unit.node.info.bindaddr.isEmpty())
                    {
                        for(auto item:Globals::getInstance()->GetVarList())
                        {
                            if(item.idname==mod_unit.node.info.bindaddr)
                            {
                                node.bind_flag=true;
                                dplcbase->m_bind_var=item;
                                break;
                            }
                        }
                    }
                    dplcbase->m_nodein_list.push_back(node);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 3:
            {
                DPLCBase *dplcbase=new DPLCM(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    node.var.type='M';
                    //绑定触发变量
                    if(!mod_unit.node.info.bindaddr.isEmpty())
                    {
                        for(auto item:Globals::getInstance()->GetVarList())
                        {
                            if(item.idname==mod_unit.node.info.bindaddr)
                            {
                                node.bind_flag=true;
                                dplcbase->m_bind_var=item;
                                break;
                            }
                        }
                    }
                    if(knob_unit.io==1)
                        dplcbase->m_nodein_list.push_back(node);
                    if(knob_unit.io==2)
                        dplcbase->m_nodeout_list.push_back(node);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 4:
            {
                DPLCBase *dplcbase=new DPLCAI(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.name=knob_unit.name;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    node.var.type='o';
                    //绑定触发变量
                    if(!mod_unit.node.info.bindaddr.isEmpty())
                    {
                        for(auto item:Globals::getInstance()->GetVarList())
                        {
                            if(item.idname==mod_unit.node.info.bindaddr)
                            {
                                node.bind_flag=true;
                                dplcbase->m_bind_var=item;
                                break;
                            }
                        }
                    }
                    dplcbase->m_nodeout_list.push_back(node);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 5:
            {
                DPLCBase *dplcbase=new DPLCAO(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    node.var.type='i';
                    //绑定触发变量
                    if(!mod_unit.node.info.bindaddr.isEmpty())
                    {
                        for(auto item:Globals::getInstance()->GetVarList())
                        {
                            if(item.idname==mod_unit.node.info.bindaddr)
                            {
                                node.bind_flag=true;
                                dplcbase->m_bind_var=item;
                                break;
                            }
                        }
                    }
                    dplcbase->m_nodein_list.push_back(node);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 19:
            {
                DPLCBase *dplcbase=new DPLCN(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    node.var.type='N';
                    //绑定触发变量
                    if(!mod_unit.node.info.bindaddr.isEmpty())
                    {
                        for(auto item:Globals::getInstance()->GetVarList())
                        {
                            if(item.idname==mod_unit.node.info.bindaddr)
                            {
                                node.bind_flag=true;
                                dplcbase->m_bind_var=item;
                                break;
                            }
                        }
                    }
                    if(knob_unit.io==1)
                        dplcbase->m_nodein_list.push_back(node);
                    if(knob_unit.io==2)
                        dplcbase->m_nodeout_list.push_back(node);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 20:
            {
                DPLCBase *dplcbase=new DPLCF(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    node.var.type='F';
                    //绑定触发变量
                    if(!mod_unit.node.info.bindaddr.isEmpty())
                    {
                        for(auto item:Globals::getInstance()->GetVarList())
                        {
                            if(item.idname==mod_unit.node.info.bindaddr)
                            {
                                node.bind_flag=true;
                                dplcbase->m_bind_var=item;
                                break;
                            }
                        }
                    }
                    if(knob_unit.io==1)
                        dplcbase->m_nodein_list.push_back(node);
                    if(knob_unit.io==2)
                        dplcbase->m_nodeout_list.push_back(node);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 6:
            {
                DPLCBase *dplcbase=new DPLCAct(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    node.var.idname=knob_unit.name;
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 7:
            {
                DPLCBase *dplcbase=new DPLCBranch(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 8:
            {
                DPLCBase *dplcbase=new DPLCAnd(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 9:
            {
                DPLCBase *dplcbase=new DPLCor(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 10:
            {
                DPLCBase *dplcbase=new DPLCnot(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 11:
            {
                DPLCBase *dplcbase =new DPLCVCC(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 12:
            {
                DPLCBase *dplcbase=new DPLCRESET(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 13:
            {
                DPLCExtBase *dplcbase=new DPLCSC(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                if(dplcbase->m_nodein_list.size()==3)
                {
                    //connect(dplcbase,&DPLCExtBase::InforAckBack,dplcbase->p_ack,&DPLCAckBase::ReturnACKStatus);
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 14:
            {
                DPLCBase *dplcbase=new DPLCDC(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 15:
            {
                DPLCBase *dplcbase=new DPLCPC(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 16:
            {
                DPLCBase *dplcbase=new DPLCSS(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 17:
            {
                DPLCBase *dplcbase=new DPLCDS(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 18:
            {
                DPLCBase *dplcbase=new DPLCCC(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 21:
            {
                DPLCBase *dplcbase=new DPLCPW(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 23:
            {
                DPLCBase *dplcbase=new DPLCTrigger(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        //绑定触发变量
                        if(!mod_unit.node.info.bindaddr.isEmpty())
                        {
                            for(auto item:Globals::getInstance()->GetVarList())
                            {
                                if(item.idname==mod_unit.node.info.bindaddr)
                                {
                                    node.bind_flag=true;
                                    dplcbase->m_bind_var=item;
                                    break;
                                }
                            }
                        }
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            case 24:
            {
                DPLCBase *dplcbase=new DPLCCW(mod_unit.node.info.name,mod_unit.node.info.guid,mod_unit.node.info.type,mod_unit.node.info.desc);
                //配置节点GUID
                for(auto knob_unit:mod_unit.node.info.knobpair)
                {
                    DPLCBase::Node node;
                    node.p_father=dplcbase;
                    node.p_id=knob_unit.guid.other;
                    node.p_self=knob_unit.guid.self;
                    node.var.idname=knob_unit.name;
                    node.var.sysid=1;
                    node.var.length=mod_unit.node.info.length.toInt();
                    if(knob_unit.io==1)
                    {
                        node.var.type='I';
                        dplcbase->m_nodein_list.push_back(node);
                    }
                    if(knob_unit.io==2)
                    {
                        node.var.type='O';
                        dplcbase->m_nodeout_list.push_back(node);
                    }
                }
                p_dplc_extlist.push_back(dplcbase);
            }
            break;

            default:
                break;
            }
        }
    }
    //连接各个模块
    QList<DPLCBase::Node*> node_in_list;
    QList<DPLCBase::Node*> node_out_list;
    for(auto mod_item:p_dplc_extlist)
    {
        for(int i=0;i<mod_item->m_nodein_list.size();++i)
            node_in_list.push_back(&mod_item->m_nodein_list[i]);
        for(int i=0;i<mod_item->m_nodeout_list.size();++i)
            node_out_list.push_back(&mod_item->m_nodeout_list[i]);
    }
    //节点连接对象
    for(auto item:node_in_list)
    {
        for(auto item_1:node_out_list)
        {
            if(item->p_id==item_1->p_self)
            {
                item->p_next=item_1;
            }
        }
    }
    //节点清空分配记录
    for(auto item:Globals::getInstance()->GetVarList())
    {
        if(item.sysid==1)
            Globals::getInstance()->DeleteVarUint(item);
    }
    //节点绑定变量
    for(auto node_unit:node_in_list)
    {
        if(node_unit->bind_flag)
        {
            if(node_unit->p_next!=nullptr)
            {
                //注册变量
                QString lname=node_unit->p_next->p_father->m_name+"."+node_unit->p_next->var.idname;
                char ltype=node_unit->p_next->var.type;
                node_unit->p_next->var=node_unit->var;
                node_unit->p_next->var.idname=lname;
                node_unit->p_next->var.type=ltype;
                Globals::getInstance()->AddVarUnit(node_unit->p_next->var);
            }
            continue;
        }
        //配置基本信息
        node_unit->var.sysid=DPLC;
        node_unit->var.idname=node_unit->p_father->m_name+"."+node_unit->var.idname;
        node_unit->var.init_value="";
        //连接对象绑定地址
        if(node_unit->p_next!=nullptr)
        {
            //注册变量
            if(Globals::getInstance()->RenameCheck(node_unit->var.idname))
            {
                if(0==Globals::getInstance()->RegisterAddr(node_unit->var.idaddr,node_unit->var.type,node_unit->var.length))
                {
                    Globals::getInstance()->AddVarUnit(node_unit->var);
                }
            }
            else        //未通过重复性检测说明已存在变量
            {
                for(auto item:Globals::getInstance()->GetVarList())
                {
                    if(item.idname==node_unit->var.idname)
                        node_unit->var=item;
                }
            }
            //注册变量
            QString lname=node_unit->p_next->p_father->m_name+"."+node_unit->p_next->var.idname;
            char ltype=node_unit->p_next->var.type;
            node_unit->p_next->var=node_unit->var;
            node_unit->p_next->var.idname=lname;
            node_unit->p_next->var.type=ltype;
            Globals::getInstance()->AddVarUnit(node_unit->p_next->var);
        }
    }
    ThreadStart();
}
/*
* 函数名：ThreadStart
* 参数：无
* 返回：无
* 功能：线程启动各个模块
*/
void DPLCServer::ThreadStart()
{
    qDebug()<<"DPLC开始运行";
    m_thread->start();
}
/*
* 函数名：run
* 参数：无
* 返回：无
* 功能：线程运行函数
*/
void DPLCServer::run()
{
    //启动前初始化，为启动作准备
    m_thread_flag=true;
    p_vcc->OnRun();
    p_reset->OnRun();
    for(auto item:p_dplc_extlist)
    {
        if(!item->OnRun())  //初始化失败，防止程序崩溃
        {
            qDebug()<<"DPLC运行初始化异常";
            Globals::getInstance()->Logging("DPLC运行初始化异常");
            //return;
        }
    }
    //p_vcc->SetValWrite(p_vcc->m_nodeout_list[0],(uint8_t)0);    //测试
    while(m_thread_flag)
    {
        if(p_vcc==nullptr || p_reset==nullptr)
        {
            qDebug()<<"缺少VCC模块或RESET模块";
            Globals::getInstance()->Logging("缺少VCC模块或RESET模块");
            QThread::msleep(1000);
            continue;
        }
        if(p_vcc->NodeValueToD(p_vcc->m_nodeout_list[0])==0)
        {
            qDebug()<<"VCC模块未开启";
            Globals::getInstance()->Logging("VCC模块未开启");
            QThread::msleep(1000);
            continue;
        }
        if(p_reset->NodeValueToD(p_reset->m_nodeout_list[0])==1)
        {
            //DPLC复位
            if(!p_reset->SetValWrite(p_reset->m_nodeout_list[0],(uint8_t)0))
            {
                qDebug()<<"系统重置失败";
                Globals::getInstance()->Logging("系统重置失败");
            }
            else
            {
                qDebug()<<"系统重置成功";
                Globals::getInstance()->Logging("系统重置成功");
            }
            QThread::msleep(1000);
            continue;
        }
        for(auto item:p_dplc_extlist)
        {
            if(!item->Run())  //运行失败，防止程序崩溃
            {
                qDebug()<<"DPLC运行失败";
                Globals::getInstance()->Logging("DPLC运行失败");
                return;
            }
        }
#ifdef TEST
        QThread::msleep(1000);
#endif
    }
}
