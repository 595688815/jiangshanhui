#ifndef SYSTEMSQL_H
#define SYSTEMSQL_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QFile>

class systemsql
{
public:
    systemsql();

    static systemsql* getInstance();
    bool ConnectToMySQL();
    bool CreateTable(const QString& tableName, const QStringList& fieldNames);
    bool InsertData(QString tablename,QStringList tabledata);
    bool DeleteData(QString tablename,QString num);
    bool DeleteTable(QString tablename);
    QSqlDatabase m_db;
private:
    static systemsql *m_sql;
};

#endif // SYSTEMSQL_H
