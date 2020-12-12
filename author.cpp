#include "author.h"

Author::Author(QString name, QString surname)
{
    this->name = name;
    this->surname = surname;
}

bool Author::validate()
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
