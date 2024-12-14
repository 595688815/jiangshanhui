#ifndef SYSTEMBASE_H
#define SYSTEMBASE_H

#include "globals.h"
/*
 * 服务器数据库基类
*/
class CSystemBase
{
public:
    SystemDataType Getsystype(){return systype;}
    QString GetId(){return id;}
    void SetId(QString value){id=value;}
protected:
    SystemDataType systype; //数据类型
    QString id;             //数据库唯一ID，作为增删减除唯一依据
};

#endif // SYSTEMBASE_H
