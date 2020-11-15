#include "address.h"

Address::Address(QString city, QString post_code, QString street, int home_nr, int flat_nr)
{
    this->city = city;
    this->post_code = post_code;
    this->street = street;
    this->home_nr = home_nr;
    this->flat_nr = flat_nr;
}

bool Address::validate()
{
    bool flag = true;
    QString error;

    QRegularExpression exp("^([a-zA-Z\u0080-\u024F]+(?:. |-| |'))*[a-zA-Z\u0080-\u024F]*");
    QRegularExpressionValidator validator(exp, 0);
    int pos = 0;

    if(city.isEmpty() || validator.validate(city, pos) == QValidator::Invalid) {
        error = "Pole miasto jest nieprawidłowe";
        flag = false;
    }

    exp.setPattern("[0-9]{2}[-]+[0-9]{3}");
    validator.setRegularExpression(exp);

    if(validator.validate(post_code, pos) == QValidator::Invalid || post_code.isEmpty()) {
        error = "Kod pocztowy jest nieprawidłowy";
        flag = false;
    }

    if(street.isEmpty()) {
        error = "Pole ulica nie może być puste";
        flag = false;
    }

    if(home_nr == 0) {
        error = "Numer domu jest nie prawidłowy";
        flag = false;
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error);
    }

    return flag;
}

int Address::push()
{
    QSqlQuery query;

    bool flag = query.prepare("INSERT INTO address VALUES(NULL, ?, ?, ?, ?, ?);");
    if(!flag) qDebug() << "prepare error" << query.lastError();
    query.addBindValue(city);
    query.addBindValue(post_code);
    query.addBindValue(street);
    query.addBindValue(home_nr);
    query.addBindValue(flat_nr);

    if(!query.exec()) {
        qDebug() << "INSERT INTO address table error:" << query.lastError();
        return -1;
    }

    id = query.lastInsertId().toInt();

    return id;
}

int Address::getID()
{
    return this->id;
}
