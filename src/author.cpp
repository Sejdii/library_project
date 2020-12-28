#include "lib/author.h"

Author::Author(QString name, QString surname)
{
    this->name = name;
    this->surname = surname;
}

bool Author::validate(bool edit)
{
    bool ok = true;
    QString error_text;

    QRegularExpression exp("^[\\w'\\-,.]*[^_!¡?÷?¿\\/\\\\+=@#$%ˆ&*(){}|~<>;:[\\]]*");
    QRegularExpressionValidator validator(exp);
    int pos = 0;

    if(validator.validate(name, pos) == QValidator::Invalid || name.isEmpty()) {
        error_text = "Podane imię jest nieprawidłowe";
        ok = false;
    }

    if(validator.validate(surname, pos) == QValidator::Invalid || surname.isEmpty()) {
        error_text = "Podane nazwisko jest nieprawidłowe";
        ok = false;
    }

    if(edit) NULL; // brak użycia pola edit dla tej tabeli

    if(!ok) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error_text);
    }

    return ok;
}

int Author::push()
{
    QSqlQuery query;
    int id;

    if(!query.prepare("INSERT INTO author VALUES (NULL, ?, ?)")) {
        qDebug() << "author push prepere error: " << query.lastError();
        return -1;
    }

    query.addBindValue(name);
    query.addBindValue(surname);

    if(!query.exec()) {
        qDebug() << "author push exec error: " << query.lastError();
        return -1;
    }

    id = query.lastInsertId().toInt();

    return id;
}

QStringList Author::get_completer_list()
{
    QSqlQuery query;
    QStringList stringlist;

    if(!query.prepare("SELECT name || ' ' || surname AS auth_name FROM author")) {
        qDebug() << "Author get completer list prepere error: " << query.lastError();
        return stringlist;
    }

    if(!query.exec()) {
        qDebug() << "Author get completer list exec error: " << query.lastError();
        return stringlist;
    }

    int field_num = query.record().indexOf("auth_name");
    while(query.next()) {
        QString name = query.value(field_num).toString();
        stringlist << name;
    }

    return stringlist;
}

int Author::get_id(QString name)
{
    QSqlQuery query;

    if(!query.prepare("SELECT id FROM author WHERE name || ' ' || surname = ?")) {
        qDebug() << "Author get id prepere error: " << query.lastError();
        return -1;
    }

    query.addBindValue(name);

    if(!query.exec()) {
        qDebug() << "Author get id exec error: " << query.lastError();
        return -1;
    }

    if(query.first()) return query.value(0).toInt();
    return -1;
}
