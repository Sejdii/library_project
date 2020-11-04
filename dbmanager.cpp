#include "dbmanager.h"
#include <QFileInfo>

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
    if(QFileInfo::exists(path) && QFileInfo(path).isFile()) {
        qDebug() << "Database already exist, initial doesnt needed";
        return false;
    }

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    database.open();
    QSqlQuery query;

    // CREATING BOOK TABLE
    QString value = "CREATE TABLE book("
               "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
               "isbn varchar(13) NOT NULL UNIQUE,"
               "title varchar(128) NOT NULL,"
               "publisher_id integer NOT NULL,"
               "publish_year YEAR NOT NULL,"
               "author varchar(255) NOT NULL,"
               "decription text NULL,"
               "cover_url varchar(255) NULL,"
               "items_nr int NOT NULL,"
               "FOREIGN KEY(publisher_id) REFERENCES publisher(id)"
               ");";
    if(!query.exec(value)) {
        qDebug() << "Add book table error: " << query.lastError();
        return false;
    }

    // CREATING PUBLISHER TABLE
    value = "CREATE TABLE publisher("
                  "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "name varchar(128) NOT NULL,"
                  "description text NULL"
                  ");";
    if(!query.exec(value)) {
        qDebug() << "Add publisher table error:" << query.lastError();
        return false;
    }

    // CREATING CLIENT TABLE
    value = "CREATE TABLE client("
                  "pesel varchar(11) NOT NULL PRIMARY KEY,"
                  "card_nr varchar(6) NOT NULL UNIQUE,"
                  "password varchar(255) NOT NULL,"
                  "name varchar(64) NOT NULL,"
                  "surname varchar(6) NOT NULL,"
                  "birthdate date NOT NULL,"
                  "city varchar(32) NOT NULL,"
                  "zip_code varchar(6) NOT NULL,"
                  "street varchar(64) NOT NULL,"
                  "house_nr int NOT NULL,"
                  "flat_nr int NULL"
                  ");";
    if(!query.exec(value)) {
        qDebug() << "Add client table error:" << query.lastError();
        return false;
    }

    // CREATING WORKER TABLE
    value = "CREATE TABLE worker("
                  "pesel varchar(11) NOT NULL PRIMARY KEY,"
                  "login varchar(16) NOT NULL UNIQUE,"
                  "password varchar(255) NOT NULL,"
                  "name varchar(64) NOT NULL,"
                  "surname varchar(64) NOT NULL"
                  ");";
    if(!query.exec(value)) {
        qDebug() << "Add worker table error:" << query.lastError();
        return false;
    }

    // CREATING RENT TABLE
   value = "CREATE TABLE rent("
                  "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "book_id int NOT NULL,"
                  "worker_id int NOT NULL,"
                  "client_id int NOT NULL,"
                  "start_date date NOT NULL,"
                  "end_date date NOT NULL,"
                  "FOREIGN KEY(book_id) REFERENCES book(id),"
                  "FOREIGN KEY(worker_id) REFERENCES worker(pesel),"
                  "FOREIGN KEY(client_id) REFERENCES client(pesel)"
                  ");";
   if(!query.exec(value)) {
       qDebug() << "Add worker table error:" << query.lastError();
       return false;
   }

    return true;
}
