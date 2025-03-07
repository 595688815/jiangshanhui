#ifndef SYSTEMSQL_H
#define SYSTEMSQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <thread>

class SystemSql
{
public:
    SystemSql();

    static SystemSql* getInstance();
    bool ConnectToMySQL(QString sqlname);
    bool CreateTable(const QString& tableName, const QStringList& fieldNames);
    bool InsertData(QString tablename,QStringList tabledata);
    bool DeleteData(QString tablename,QString num);
    bool DeleteTable(QString tablename);
    void InitMysql();
    QSqlDatabase m_db;
private:
    static SystemSql *m_sql;
};

#endif // SYSTEMSQL_H
