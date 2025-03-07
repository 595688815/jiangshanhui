#include "systemsql.h"
#include "Globals/globals.h"

SystemSql *SystemSql::m_sql=nullptr;

SystemSql::SystemSql()
{

}
/*
* 函数名：ConnectToMySQL
* 参数：无
* 返回：bool
* 功能：打开MYSQL
*/
bool SystemSql::ConnectToMySQL(QString sqlname)
{
    m_db=QSqlDatabase::addDatabase("QMYSQL");
    m_db.setHostName("localhost");
    m_db.setDatabaseName(sqlname);
    m_db.setUserName("root");
    m_db.setPassword("123456");
    if(!m_db.open()){
        qDebug() << "数据库连接失败：" << m_db.lastError();
        Globals::getInstance()->Logging("数据库连接失败：" + m_db.lastError().text());
        return false;
    }
    qDebug()<<"Connect Success!";
    return true; // 连接数据库成功
}
/*
* 函数名：getInstance
* 参数：无
* 返回：SystemSql*
* 功能：返回单例
*/
SystemSql* SystemSql::getInstance()
{
    //单例模式
    if(nullptr==m_sql){
        m_sql=new SystemSql();
    }
    return m_sql;
}
/*
* 函数名：CreateTable
* 参数：const QString&，const QStringList&
* 返回：bool
* 功能：创建名为arg1的数据表格，列内容由arg2决定，失败返回false，成功返回true
*/
bool SystemSql::CreateTable(const QString& tableName, const QStringList& fieldNames)
{
    QSqlQuery sql;
    QString createTableQuery = QString("CREATE TABLE %1 (").arg(tableName);
    for (int i = 0; i < fieldNames.size(); ++i)
    {
        createTableQuery += QString("%1 VARCHAR(255)").arg(fieldNames[i]);
        if (i != fieldNames.size() - 1)
        {
            createTableQuery += ", "; // 添加逗号分隔字段
        }
    }
    createTableQuery += ");"; // 结束 CREATE TABLE 语句
    if (!sql.exec(createTableQuery))
    {
        qDebug() << createTableQuery;
        qDebug() << "创建表失败";
        qDebug() <<sql.lastError().text();
        return false;
    }
    return true;
}
/*
* 函数名：InsertData
* 参数：QString，QStringList
* 返回：bool
* 功能：向arg1的数据表格添加数据，内容由arg2决定，失败返回false，成功返回true
*/
bool SystemSql::InsertData(QString tablename,QStringList tabledata)
{
    if(tabledata.size()<1)
        return false;
    QString sql="insert into ";
    sql+=tablename;
    sql+=" values(";
    for(int i=0;i<tabledata.size()-1;++i)
    {
        sql+="'";
        sql+=tabledata[i];
        sql+="',";
    }
    sql+="'";
    sql+=tabledata[tabledata.size()-1];
    sql+="')";
    qDebug() << sql;

    QSqlQuery qsql(m_db);
    if (!qsql.exec(sql))
    {
        qDebug() << "添加成功";
        return false;
    }
    return true;
}
/*
* 函数名：DeleteData
* 参数：QString，QString
* 返回：bool
* 功能：删除表格名为tablename的序列号为num的数据，每个数据都有自己唯一序列号
*/
bool SystemSql::DeleteData(QString tablename,QString num)
{
    if(tablename==""||num=="")
        return false;
    QString sql="delete from ";
    sql+=tablename;
    sql+=" where DataID = ";
    sql+=num;

    QSqlQuery qsql(m_db);
    if (!qsql.exec(sql))
    {
        qDebug() << "添加成功";
        return false;
    }
    return true;
}
/*
* 函数名：DeleteTable
* 参数：QString
* 返回：bool
* 功能：删除名为tablename的表格
*/
bool SystemSql::DeleteTable(QString tablename)
{
    if(tablename=="")
        return false;
    QString sql="drop table ";
    sql+=tablename;

    QSqlQuery qsql(m_db);
    if (!qsql.exec(sql))
    {
        qDebug() << "添加成功";
        return false;
    }
    return true;
}
/*
* 函数名：InitFromMysql
* 参数：无
* 返回：无
* 功能：初始化数据库
*/
void SystemSql::InitMysql()
{

}
