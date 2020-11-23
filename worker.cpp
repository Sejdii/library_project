#include "worker.h"

Worker::Worker(int type, QString name, QString surname)
{
    this->type = type;
    this->name = name;
    this->surname = surname;
}

Worker::Worker(User user)
{
    set_user(user);
}

Worker::Worker(unsigned int id)
{
    this->id = id;
}

int Worker::push()
{
    QSqlQuery query;

    if(!query.prepare("INSERT INTO worker VALUES(NULL, ?, ?, ?, ?, ?)")) {
        qDebug() << query.lastError();
        return -1;
    }
    query.addBindValue(type);
    query.addBindValue(login);
    query.addBindValue(password);
    query.addBindValue(name);
    query.addBindValue(surname);

    if(!query.exec()) {
        qDebug() << "worker push error " << query.lastError();
        return -1;
    }

    int id = query.lastInsertId().toInt();
    return id;
}

void Worker::set_user(User user)
{
    login = user.getLogin();
    password = user.getPassword();
}

void Worker::set_id(unsigned int id)
{
    this->id = id;
}

void Worker::fetch_worker_data()
{
    QSqlQuery query;

    if(!query.prepare("SELECT * FROM worker WHERE id = ?")) {
        qDebug() << "fetch worker prepare: " << query.lastError();
    }
    query.addBindValue(id);

    if(!query.exec()) {
        qDebug() << "fetch worker: " << query.lastError();
    }

    query.first();
    type = query.value(1).toInt();
    login = query.value(1).toString();
    password = query.value(1).toString();
    name = query.value(4).toString();
    surname = query.value(5).toString();
}

QString Worker::getName()
{
    return name;
}

int Worker::getType()
{
    return type;
}
