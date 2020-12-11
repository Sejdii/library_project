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
    login = query.value(2).toString();
    password = query.value(3).toString();
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

bool Worker::validate()
{
    bool flag = true;
    QString error;

    QRegularExpression exp("^[\\w'\\-,.]*[^_!¡?÷?¿\\/\\\\+=@#$%ˆ&*(){}|~<>;:[\\]]*");
    QRegularExpressionValidator validator(exp);
    int pos = 0;

    if(validator.validate(name, pos) == QValidator::Invalid || name.isEmpty()) {
        error = "Podane imię jest nieprawidłowe";
        flag = false;
    }

    if(validator.validate(surname, pos) == QValidator::Invalid || surname.isEmpty()) {
        error = "Podane nazwisko jest nieprawidłowe";
        flag = false;
    }

    if(!login_unique(ACCOUNT_WORKER)) {
        error = "Podany login jest już zajęty. Użyj innego";
        flag = false;
    }

    if(type != 0 && type != 1) {
        error = "Podany typ użytkownika jest niepoprawny";
        flag = false;
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error);
    }

    return flag;
}
