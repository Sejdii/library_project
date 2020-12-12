#include "publisher.h"

Publisher::Publisher(QString name, QString description)
{
    this->name = name;
    this->description = description;
}

bool Publisher::validate()
{
    bool flag = true;
    QString error_text;

    if(name.length() == 0 || name.length() > 128) {
        error_text = "Nazwa wydawcy nie może być polem pustym oraz nie może posiadać więcej niż 128 znaków";
        flag = false;
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error_text);
    }

    return flag;
}

int Publisher::push()
{
    QSqlQuery query;
    int id;

    if(!query.prepare("INSERT INTO publisher VALUES (NULL, ?, ?);")) {
        qDebug() << "push publisher prepere error: " << query.lastError();
        return -1;
    }

    query.addBindValue(name);
    query.addBindValue(description);

    if(!query.exec()) {
        qDebug() << "push publisher exec error: " << query.lastError();
        return -1;
    }

    id = query.lastInsertId().toInt();

    return id;
}
