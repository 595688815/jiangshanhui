#ifndef DPLCBASE_H
#define DPLCBASE_H
/*
 * DPLC基类
 */
#include <QTimer>
#include <QObject>
#include "Globals/globals.h"

class DPLCBase:public QObject
{
public:
    struct Node
    {
        DPLCBase *p_father;         //父类指针
        QString name;
        QString p_id;               //节点指向id，输入节点则为发起者位号
        QString p_self;             //节点自身id
        Node* p_next=nullptr;       //节点指针
        char type;
        VarUnit var;                //绑定变量
        bool bind_flag=false;       //是否已绑定变量
    };
    DPLCBase(QString name,QString id,uint8_t type,QString desc);

    virtual bool Run(){};
    virtual bool OnRun(){};
    //DPLC模块绑定单个变量获取值
    sReadVarRet GetValRead(Node node);
    uint8_t NodeValueToD(Node node);
    uint16_t NodeValueToA(Node node);
    float NodeValueToF(Node node);
    uint32_t NodeValueToN(Node node);
    QByteArray NodeValueToM(Node node);
    //DPLC模块绑定单个变量写入值
    bool SetValWrite(Node node,uint8_t value);
    bool SetValWrite(Node node,uint16_t value);
    bool SetValWrite(Node node,uint32_t value);
    bool SetValWrite(Node node,float value);
    bool SetValWrite(Node node,QByteArray value);

    bool CheckClassFlag(QString msg);

    uint8_t m_type;
    QString m_id;
    QString m_name;
    QList<Node> m_nodein_list;
    QList<Node> m_nodeout_list;
    QString m_desc;
    bool m_class_creat_flag;    //文件解析结果实例化是否符合,针对固定节点
    VarUnit m_bind_var;         //绑定非DPLC变量，用于DPLC与外部数据交互接口
};

#endif // DPLCBASE_H
