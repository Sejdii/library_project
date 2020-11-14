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

    if(validator.validate(post_code, pos) == QValidator::Invalid) {
        error = "Kod pocztowy jest nieprawidłowy";
        flag = false;
    }

    if(street.isEmpty()) {
        error = "Pole ulica nie może być puste";
        flag = false;
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error);
    }

    return flag;
}
