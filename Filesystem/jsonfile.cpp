#include "jsonfile.h"

JsonFile *JsonFile::m_instance=nullptr;

using namespace std;
JsonFile::JsonFile()
{

}
/*
* 函数名：getInstance
* 参数：无
* 返回：Globals*
* 功能：返回单例
*/
JsonFile* JsonFile::getInstance()
{
    //单例模式
    if(nullptr==m_instance){
        m_instance=new JsonFile();
    }
    return m_instance;
}
/*
* 函数名：ReadJsonFile
* 参数：QString
* 返回：bool
* 功能：解析Json文件内容
*/
bool JsonFile::ReadJsonFile(QString filePath)
{
    //Json配置文件
    /*QFile file_sys("json.sys");
    if (!file_sys.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open json.sys.";
        return false;
    }
    while(!file_sys.atEnd())
    {
        QByteArray str=file_sys.readLine();
        if(str.startsWith("//"))    //注释行直接跳过
            continue;
        //筛除干扰字符串
        str.replace("\n","");
        str.replace(";","");

        if(str.startsWith("@DI"))
        {

        }
    }
    file_sys.close();*/
    //打开JSON文件
    QFile file_json(filePath);
    if(!file_json.open(QIODevice::ReadOnly))
    {
        qDebug() << "无法打开文件" << filePath;
        return false;
    }
    QByteArray fileData = file_json.readAll();
    file_json.close();

    QJsonDocument document = QJsonDocument::fromJson(fileData);
    //qDebug()<<document;
    if (filePath=="NodeConfigTable.json"
        ||filePath=="DPLCNodeConfig.json"
        ||filePath=="NodeConfigTable1.json")
    {
        m_jsonobject = document.object();
        QList<QPair<QString,QList<Module>*>> pairvarlist;
        QPair<QString,QList<Module>*> pairvar;
        //mozu
        pairvar.first="mozuList";
        pairvar.second=Globals::getInstance()->GetModuleList();
        pairvarlist.push_back(pairvar);
        //gongwei
        pairvar.first="gongweiList";
        pairvar.second=Globals::getInstance()->GetStationList();
        pairvarlist.push_back(pairvar);
        //setting
        for(int i=0;i<m_jsonobject["setting"].toArray().size();i++)
        {

        }
        //mozuList  gongweiList
        for(int listconut=0;listconut<pairvarlist.size();listconut++)
        {
            QString tmpstr=pairvarlist[listconut].first;
            pairvarlist[listconut].second->clear();
            for(int i=0;i<m_jsonobject[tmpstr].toArray().size();i++)
            {
                Module module;
                module.group=m_jsonobject[tmpstr].toArray()[i].toObject()["group"].toString();
                module.name=m_jsonobject[tmpstr].toArray()[i].toObject()["name"].toString();
                // qDebug()<<module.group;
                // qDebug()<<module.name;
                for(int j=0;j<m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray().size();j++)
                {
                    Module_TwoD twod;
                    twod.node.info.guid=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["guid"].toString();
                    twod.node.info.name=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["name"].toString();
                    twod.node.info.type=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["type"].toInt();
                    twod.node.info.length=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["varLen"].toString();
                    twod.node.info.bindaddr=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["bindAddr"].toString();
                    twod.node.info.refresh=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["refresh"].toString();
                    twod.node.info.desc=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["desc"].toString();
                    twod.node.info.addr=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["addr"].toString();
                    //qDebug()<<m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j];
                    for(int z=0;z<m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["knobpair"].toArray().size();++z)
                    {
                        Module_TwoD_Node_Info_Knobpair knobpair;
                        knobpair.io=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["knobpair"].toArray()[z].toObject()["io"].toInt();
                        knobpair.id=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["knobpair"].toArray()[z].toObject()["id"].toInt();
                        knobpair.name=m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["knobpair"].toArray()[z].toObject()["name"].toString();
                        knobpair.guid.self =
                            m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["knobpair"].toArray()[z].toObject()["guid"].toObject()["self"].toString();
                        knobpair.guid.other =
                            m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["knobpair"].toArray()[z].toObject()["guid"].toObject()["other"].toString();
                        twod.node.info.knobpair.push_back(knobpair);
                        //qDebug()<<m_jsonobject[tmpstr].toArray()[i].toObject()["twoD"].toArray()[j].toObject()["node"].toObject()["nodeinfo"].toObject()["knobpair"].toArray()[z].toObject()["guid"].toObject()["self"].toString();
                    }
                    module.twod.push_back(twod);
                }
                pairvarlist[listconut].second->push_back(module);
            }
        }
    }
    if (filePath=="ioconfig.json")
    {
        IOConfig *ioconfig=Globals::getInstance()->GetIOConfig();
        m_jsonobject = document.object();
        ioconfig->ip=m_jsonobject["ip"].toString();
        ioconfig->port=m_jsonobject["port"].toInt();
        ioconfig->socket=m_jsonobject["socket"].toString();
        ioconfig->sport=m_jsonobject["sport"].toInt();
        ioconfig->sn=m_jsonobject["sn"].toString();
        ioconfig->IO.clear();
        for(int i=0;i<m_jsonobject["IO"].toArray().size();++i)
        {
            IOConfig_IO ioconfig_io;
            ioconfig_io.type=m_jsonobject["IO"].toArray()[i].toObject()["type"].toInt();
            ioconfig_io.name=m_jsonobject["IO"].toArray()[i].toObject()["name"].toString();
            ioconfig_io.addr=m_jsonobject["IO"].toArray()[i].toObject()["addr"].toString();
            ioconfig_io.desc=m_jsonobject["IO"].toArray()[i].toObject()["desc"].toString();
            for(int j=0;j<m_jsonobject["IO"].toArray()[i].toObject()["input"].toArray().size();++j)
            {
                IOConfig_IO_io ioconfig_io_io;
                ioconfig_io_io.id=QString::number(j+1);
                ioconfig_io_io.name=m_jsonobject["IO"].toArray()[i].toObject()["input"].toArray()[j].toObject()[QString::number(j+1)].toString();
                ioconfig_io.input.push_back(ioconfig_io_io);
            }
            for(int j=0;j<m_jsonobject["IO"].toArray()[i].toObject()["output"].toArray().size();++j)
            {
                IOConfig_IO_io ioconfig_io_io;
                ioconfig_io_io.id=QString::number(j+1);
                ioconfig_io_io.name=m_jsonobject["IO"].toArray()[i].toObject()["output"].toArray()[j].toObject()[QString::number(j+1)].toString();
                ioconfig_io.output.push_back(ioconfig_io_io);
            }
            for(int j=0;j<m_jsonobject["IO"].toArray()[i].toObject()["addition"].toArray().size();++j)
            {
                IOConfig_IO_addition ioconfig_io_addition;
                ioconfig_io_addition.type=m_jsonobject["IO"].toArray()[i].toObject()["addition"].toArray()[j].toObject()["type"].toString();
                ioconfig_io_addition.name=m_jsonobject["IO"].toArray()[i].toObject()["addition"].toArray()[j].toObject()["name"].toString();
                ioconfig_io.addtion.push_back(ioconfig_io_addition);
            }
            ioconfig->IO.push_back(ioconfig_io);
        }
    }
    //验证环节
    // QList<Module> m_module_list = *Globals::getInstance()->GetModuleList();
    // for(int i=0;i<m_module_list.size();i++)
    // {
    //     qDebug()<<"Module"<<i<<":";
    //     qDebug()<<"group="<<m_module_list[i].group;
    //     qDebug()<<"name="<<m_module_list[i].name;
    //     qDebug()<<"twoD:";
    //     qDebug()<<"     node:";
    //     for(int j=0;j<m_module_list[i].twod.size();++j)
    //     {
    //         qDebug()<<"         nodeinfo";
    //         qDebug()<<"             guid="<<m_module_list[i].twod[j].node.info.guid;
    //         qDebug()<<"             name="<<m_module_list[i].twod[j].node.info.name;
    //         qDebug()<<"             type="<<m_module_list[i].twod[j].node.info.type;
    //         qDebug()<<"             desc="<<m_module_list[i].twod[j].node.info.desc;
    //         qDebug()<<"             addr="<<m_module_list[i].twod[j].node.info.addr;
    //         qDebug()<<"             refresh="<<m_module_list[i].twod[j].node.info.refresh;
    //         qDebug()<<"             bindaddr="<<m_module_list[i].twod[j].node.info.bindaddr;
    //         for(int z=0;z<m_module_list[i].twod[j].node.info.knobpair.size();++z)
    //         {
    //             qDebug()<<"             knobpair";
    //             qDebug()<<"                 id="<<m_module_list[i].twod[j].node.info.knobpair[z].id;
    //             qDebug()<<"                 io="<<m_module_list[i].twod[j].node.info.knobpair[z].io;
    //             qDebug()<<"                 guid";
    //             qDebug()<<"                     self="<<m_module_list[i].twod[j].node.info.knobpair[z].guid.self;
    //             qDebug()<<"                     other="<<m_module_list[i].twod[j].node.info.knobpair[z].guid.other;
    //         }
    //     }
    // }
    //IOConfig *ioconfig=Globals::getInstance()->GetIOConfig();
    return true;
}
/*
* 函数名：VarToJsonFile
* 参数：MyTcpSocket *
* 返回：无
* 功能：向指定端口发送Json文件
*/
void JsonFile::VarToJsonFile(MyTcpSocket *socket)
{
    socket->SendMsg(VarToJsonByteArray());
}
/*
* 函数名：VarToJsonFile
* 参数：无
* 返回：无
* 功能：向所有客户端发送Json文件
*/
void JsonFile::VarToJsonFile()
{
    for(auto item:Tcpserver::getInstance()->GetTcpList())
    {
        item->SendMsg(VarToJsonByteArray());
    }
}
/*
* 函数名：VarToJsonByteArray
* 参数：无
* 返回：QByteArray
* 功能：变量转换成字符串
*/
QByteArray JsonFile::VarToJsonByteArray()
{
    QJsonObject jsonobject;
    QJsonArray jsonArray;
    QByteArray ret_str="";
    for(auto item:Globals::getInstance()->GetVarList())
    {
        QJsonObject jsonobject_unit;
        jsonobject_unit["sysid"]=item.sysid;
        jsonobject_unit["name"] = item.idname;
        jsonobject_unit["type"] = QString(item.type);
        jsonobject_unit["addr"] = QJsonValue::fromVariant(item.idaddr);
        jsonobject_unit["length"] = QJsonValue::fromVariant(item.length);
        jsonobject_unit["desc"]=item.desc;
        sReadVarPar var;
        var.num=1;
        var.type=item.type;
        var.addr=item.idaddr;
        var.length=item.length;
        //取值
        sReadVarRet ret = Globals::getInstance()->ReadVar(var);
        if(ret.value.size()<ret.length)
        {
            qDebug()<<"读取数据出错，读取字节数小于数据长度";
            return ret_str;
        }
        switch (ret.type) {
        case 'I':
        case 'O':
            jsonobject_unit["value"]=ret.value[0];
            break;

        case 'i':
        case 'o':
            jsonobject_unit["value"]=(ret.value[0]<<8)+ret.value[1];
            break;

        case 'N':
            jsonobject_unit["value"]=(ret.value[0]<<24)
                                        +(ret.value[1]<<16)
                                        +(ret.value[2]<<8)
                                        +(ret.value[3]);
            break;

        case 'F':
        {
            uint8_t ch[4];
            ch[0]=ret.value[0];
            ch[1]=ret.value[1];
            ch[2]=ret.value[2];
            ch[3]=ret.value[3];
            jsonobject_unit["value"]=*((float*)ch);
        }
        break;

        case 'M':
        {
            char *str=new char[ret.value.size()];
            for(int i=0;i<ret.value.size();i++)
            {
                str[i]=ret.value[i];
            }
            jsonobject_unit["value"]=str;
            delete str;
        }
        break;

        default:
            break;
        }
        jsonArray.append(jsonobject_unit);
    }
    jsonobject["var"]=jsonArray;
    QJsonDocument doc(jsonobject);
    ret_str=doc.toJson();
    ret_str.append("EOF");
    return ret_str;
}
