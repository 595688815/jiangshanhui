#ifndef SYSTEMBASEOPERATIONS_H
#define SYSTEMBASEOPERATIONS_H
#include "systembase.h"
//操作
class CSystemBaseOperations : public CSystemBase
{
public:
    CSystemBaseOperations(){systype=ST_Operation;}

    QString GetOpid(){return m_opid;}
    void SetOpid(QString str){m_opid = str;}
    QString GetOpname(){return m_opname;}
    void SetOpname(QString str){m_opname = str;}
    QString GetOpsCnt(){return m_opsCnt;}
    void SetOpsCnt(QString str){m_opsCnt = str;}
private:
    QString m_opid;     //操作ID
    QString m_opname;   //操作名称
    QString m_opsCnt;   //权限计数
};

#endif // SYSTEMBASEOPERATIONS_H
