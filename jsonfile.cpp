#include "jsonfile.h"

JsonFile::JsonFile() {}

/*
* 函数名：ReadJsonFile
* 参数：const QString &
* 返回：bool
* 功能：读取Json文件内容
*/
bool JsonFile::ReadJsonFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "无法打开文件" << filePath;
        return false;
    }
    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(fileData);

    if (document.isObject())
    {
        m_jsonobject = document.object();
        //
        for(int i=0;i<m_jsonobject["layout"].toArray().size();i++)
        {
            Layout* instance=new Layout;
            instance->guid=m_jsonobject["layout"][i]["guid"].toString();
            instance->name=m_jsonobject["layout"][i]["name"].toString();
            instance->type=m_jsonobject["layout"][i]["type"].toInt();

            instance->setting.resolutionw=m_jsonobject["layout"][i]["setting"]["resolutionw"].toInt();
            instance->setting.resolutionh=m_jsonobject["layout"][i]["setting"]["resolutionh"].toInt();
            instance->setting.bgurl=m_jsonobject["layout"][i]["setting"]["bgurl"].toString();

            for(int j=0;j<m_jsonobject["layout"][i]["components"].toArray().size();j++)
            {
                Components *lcomponents=new Components;
                lcomponents->guid=m_jsonobject["layout"][i]["components"][j]["guid"].toString();
                lcomponents->name=m_jsonobject["layout"][i]["components"][j]["name"].toString();
                lcomponents->type=m_jsonobject["layout"][i]["components"][j]["type"].toInt();

                lcomponents->prop.x=m_jsonobject["layout"][i]["components"][j]["prop"]["x"].toString();
                lcomponents->prop.y=m_jsonobject["layout"][i]["components"][j]["prop"]["y"].toString();
                lcomponents->prop.w=m_jsonobject["layout"][i]["components"][j]["prop"]["w"].toString();
                lcomponents->prop.h=m_jsonobject["layout"][i]["components"][j]["prop"]["h"].toString();
                lcomponents->prop.text=m_jsonobject["layout"][i]["components"][j]["prop"]["text"].toString();
                lcomponents->prop.size=m_jsonobject["layout"][i]["components"][j]["prop"]["size"].toString();
                lcomponents->prop.var=m_jsonobject["layout"][i]["components"][j]["prop"]["var"].toString();
                lcomponents->prop.txtcolor=m_jsonobject["layout"][i]["components"][j]["prop"]["txtcolor"].toString();
                lcomponents->prop.imgcolor=m_jsonobject["layout"][i]["components"][j]["prop"]["imgcolor"].toString();

                instance->components.push_back(*lcomponents);
            }
            m_layout_list.push_back(*instance);
        }
    }
    else if (document.isArray())
    {
        QJsonArray jsonArray = document.array();
        qDebug() << "读取到的JSON数组:" << jsonArray;
    }
    else
    {
        qDebug() << "无法识别的JSON文档类型";
    }
    //验证环节
    // for(int i=0;i<m_layout_list.size();i++)
    // {
    //     qDebug()<<"layout"<<i<<":\n";
    //     qDebug()<<"guid="<<m_layout_list[i].guid;
    //     qDebug()<<"name="<<m_layout_list[i].name;
    //     qDebug()<<"type="<<m_layout_list[i].type;
    //     qDebug()<<"setting:\n";
    //     qDebug()<<"     resolutionw="<<m_layout_list[i].setting.resolutionw;
    //     qDebug()<<"     resolutionh="<<m_layout_list[i].setting.resolutionh;
    //     qDebug()<<"     bgurl="<<m_layout_list[i].setting.bgurl;

    //     for(int j=0;j<m_layout_list[i].components.size();++j)
    //     {
    //         qDebug()<<"components"<<j+":\n";
    //         qDebug()<<"     guid="<<m_layout_list[i].components[j].guid;
    //         qDebug()<<"     name="<<m_layout_list[i].components[j].name;
    //         qDebug()<<"     type="<<m_layout_list[i].components[j].type;
    //         qDebug()<<"     prop:\n";
    //         qDebug()<<"         x="<<m_layout_list[i].components[j].prop.x;
    //         qDebug()<<"         y="<<m_layout_list[i].components[j].prop.y;
    //         qDebug()<<"         w="<<m_layout_list[i].components[j].prop.w;
    //         qDebug()<<"         h="<<m_layout_list[i].components[j].prop.h;
    //         qDebug()<<"         text="<<m_layout_list[i].components[j].prop.text;
    //         qDebug()<<"         size="<<m_layout_list[i].components[j].prop.size;
    //         qDebug()<<"         var="<<m_layout_list[i].components[j].prop.var;
    //         qDebug()<<"         txtcolor="<<m_layout_list[i].components[j].prop.txtcolor;
    //         qDebug()<<"         imgcolor="<<m_layout_list[i].components[j].prop.imgcolor;
    //     }
    // }
    //记录日志
    QString logstr="";
    for(int i=0;i<m_layout_list.size();i++)
    {
        logstr += "layout"+QString::number(i)+":\n";
        logstr += "guid="+m_layout_list[i].guid+"\n";
        logstr += "name="+m_layout_list[i].name+"\n";
        logstr += "type="+QString::number(m_layout_list[i].type)+"\n";
        logstr += "setting:\n";
        logstr += "     resolutionw="+QString::number(m_layout_list[i].setting.resolutionw)+"\n";
        logstr += "     resolutionh="+QString::number(m_layout_list[i].setting.resolutionh)+"\n";
        logstr += "     bgurl="+m_layout_list[i].setting.bgurl+"\n";
        for(int j=0;j<m_layout_list[i].components.size();++j)
        {
            logstr += "components"+QString::number(j)+":\n";
            logstr += "     guid="+m_layout_list[i].components[j].guid+"\n";
            logstr += "     name="+m_layout_list[i].components[j].name+"\n";
            logstr += "     type="+QString::number(m_layout_list[i].components[j].type)+"\n";
            logstr += "     prop:\n";
            logstr += "         x="+m_layout_list[i].components[j].prop.x+"\n";
            logstr += "         y="+m_layout_list[i].components[j].prop.y+"\n";
            logstr += "         w="+m_layout_list[i].components[j].prop.w+"\n";
            logstr += "         h="+m_layout_list[i].components[j].prop.h+"\n";
            logstr += "         text="+m_layout_list[i].components[j].prop.text+"\n";
            logstr += "         size="+m_layout_list[i].components[j].prop.size+"\n";
            logstr += "         var="+m_layout_list[i].components[j].prop.var+"\n";
            logstr += "         txtcolor="+m_layout_list[i].components[j].prop.txtcolor+"\n";
            logstr += "         imgcolor="+m_layout_list[i].components[j].prop.imgcolor+"\n";
        }
    }
    Globals::getInstance()->Logging(logstr);
    return true;
}
