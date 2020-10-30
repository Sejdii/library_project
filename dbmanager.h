#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>

const QString DATABASE_PATH = "library.db";

class DBManager
{
public:
    DBManager(const QString& path);
    static bool initial_database(const QString& path);

private:
    QSqlDatabase database;
};

#endif // DBMANAGER_H
