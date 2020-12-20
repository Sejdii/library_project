#include "publisher.h"

Publisher::Publisher(QString name, QString description)
{
    this->name = name;
    this->description = description;
}

bool Publisher::validate(bool edit)
{
    bool flag = true;
    QString error_text;

    if(name.length() == 0 || name.length() > 128) {
        error_text = "Nazwa wydawcy nie może być polem pustym oraz nie może posiadać więcej niż 128 znaków";
        flag = false;
    }

    if(!check_name_unique() && !edit) {
        error_text = "Nazwa wydawcy już istnieje w bazie";
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

QStringList Publisher::get_completer_list()
{
    QSqlQuery query;
    QStringList stringlist;

    if(!query.prepare("SELECT name FROM publisher")) {
        qDebug() << "get completer list prepere error: " << query.lastError();
        return stringlist;
    }

    if(!query.exec()) {
        qDebug() << "get completer list exec error: " << query.lastError();
        return stringlist;
    }

    int field_num = query.record().indexOf("name");
    while(query.next()) {
        QString name = query.value(field_num).toString();
        stringlist << name;
    }

    return stringlist;
}


bool Publisher::check_name_unique()
{
    QSqlQuery query;

    if(!query.prepare("SELECT id FROM publisher WHERE name=?")) {
        qDebug() << "Publisher check name unique prepere error: " << query.lastError();
    }

    query.addBindValue(name);

    if(!query.exec()) {
        qDebug() << "Publisher check name unique exec error: " << query.lastError();
    }

    if(query.first()) return false;
    return true;
}
