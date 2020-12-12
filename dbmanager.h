#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>

#include "worker.h"

/**
 * @brief DATABASE_PATH ścieżka do pliku bazy danych
 */
const QString DATABASE_PATH = "library.db";

/**
 * @brief Klasa DBManger do zarządzania bazą danych
 */
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
