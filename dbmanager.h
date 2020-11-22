#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>

#include "worker.h"

const QString DATABASE_PATH = "library.db";

class DBManager
{
public:
    DBManager(const QString& path);
    static bool initial_database(const QString& path, bool force=false);

    QSqlDatabase get_database();

private:
    QSqlDatabase database;
};

#endif // DBMANAGER_H
