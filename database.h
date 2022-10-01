#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>

class Database : public QObject
{
public:
    explicit Database(QObject *parent = nullptr);

    void createDatabase(const QString &name);
    bool openDatabase(const QString &nameDatabase);

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
