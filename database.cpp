#include "database.h"

Database::Database(QObject *parent) :
    QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

void Database::createDatabase(const QString &name)
{
    m_db.setDatabaseName(name);
    m_db.open();
}

bool Database::openDatabase(const QString &nameDatabase)
{
    m_db.setDatabaseName(nameDatabase);
    return m_db.open();
}
