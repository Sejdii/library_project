#include "dbmanager.h"

DBManager::DBManager(const QString& path)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);

    if(!database.open()) {
        qDebug() << "Connection with database error";
    } else {
        qDebug() << "Connection with database success";
    }
}

bool DBManager::initial_database(const QString& path)
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.open();
    QSqlQuery query;

    // CREATING BOOK TABLE
    query.prepare("CREATE TABLE book("
               "id int NOT NULL PRIMARY KEY AUTO_INCREMENT,"
               "isbn varchar(13) NOT NULL,"
               "title varchar(128) NOT NULL,"
               "publisher_id int NOT NULL,"
               "publish_year YEAR NOT NULL,"
               "author varchar(255) NOT NULL,"
               "decription text NULL,"
               "cover_url varchar(255) NULL,"
               "items_nr int NOT NULL"
               ");");
    if(!query.exec()) {
        qDebug() << "Add book table error: " << query.lastError();
        return false;
    }

    // CREATING PUBLISHER TABLE
    query.prepare("CREATE TABLE publisher("
                  "id int NOT NULL PRIMARY KEY AUTO_INCREMENT,"
                  "name varchar(128) NOT NULL,"
                  "description text NULL"
                  ");");
    if(!query.exec()) {
        qDebug() << "Add publisher table error:" << query.lastError();
        return false;
    }

    return true;
}
