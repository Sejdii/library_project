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

bool DBManager::initial_database(const QString& path, bool force)
{
    if(QFileInfo::exists(path) && QFileInfo(path).isFile()) {
        if(force == true) {
            QFile file;
            file.remove(DATABASE_PATH);
            qDebug() << "Database force again initiation";
        } else {
            qDebug() << "Database already exist, initial doesnt needed";
            return false;
        }
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
               "decription text NULL,"
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

    // CREATING ADDRESS TABLE
    value = "CREATE TABLE address("
            "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
            "city varchar(32) NOT NULL,"
            "post_code varchar(6) NOT NULL,"
            "street varchar(64) NOT NULL,"
            "house_nr int NOT NULL,"
            "flat_nr int NULL"
            ");";
    if(!query.exec(value)) {
        qDebug() << "Add address table error:" << query.lastError();
        return false;
    }

    // CREATING CLIENT TABLE
    value = "CREATE TABLE client("
                  "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "login varchar(16) NOT NULL UNIQUE,"
                  "password varchar(255) NOT NULL,"
                  "pesel varchar(11) NOT NULL,"
                  "name varchar(64) NOT NULL,"
                  "surname varchar(6) NOT NULL,"
                  "email varchar(255) NOT NULL,"
                  "address_id integer NOT NULL,"
                  "FOREIGN KEY(address_id) REFERENCES address(id)"
                  ");";
    if(!query.exec(value)) {
        qDebug() << "Add client table error:" << query.lastError();
        return false;
    }

    // CREATING WORKER TABLE
    value = "CREATE TABLE worker("
                  "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
                  "pesel varchar(11) NOT NULL UNIQUE,"
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
                  "book_id integer NOT NULL,"
                  "worker_id integer NOT NULL,"
                  "client_id integer NOT NULL,"
                  "start_date date NOT NULL,"
                  "end_date date NOT NULL,"
                  "FOREIGN KEY(book_id) REFERENCES book(id),"
                  "FOREIGN KEY(worker_id) REFERENCES worker(id),"
                  "FOREIGN KEY(client_id) REFERENCES client(id)"
                  ");";
   if(!query.exec(value)) {
       qDebug() << "Add worker table error:" << query.lastError();
       return false;
   }

   // CREATING AUTHOR TABLE
   value = "CREATE TABLE author("
           "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
           "name VARCHAR(64) NOT NULL,"
           "surname VARCHAR(64) NOT NULL"
           ");";
   if(!query.exec(value)) {
       qDebug() << "Add author table error:" << query.lastError();
       return false;
   }

   // CREATING BOOK_AUTHOR TABLE
   value = "CREATE TABLE book_author("
           "id integer NOT NULL PRIMARY KEY AUTOINCREMENT,"
           "book_id integer NOT NULL,"
           "author_id integer NOT NULL,"
           "FOREIGN KEY(book_id) REFERENCES book(id),"
           "FOREIGN KEY(author_id) REFERENCES author(id)"
           ");";
   if(!query.exec(value)) {
       qDebug() << "Add book_author table error:" << query.lastError();
       return false;
   }


    return true;
}
