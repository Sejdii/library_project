#include "client.h"

Client::Client(QString pesel, QString name, QString surname, QString email)
{
    this->pesel = pesel;
    this->name = name;
    this->surname = surname;
    this->email = email;
}

bool Client::validate()
{
    bool flag = true;
    QString error;

    QRegularExpression exp("^[0-9]{11}");
    QRegularExpressionValidator validator(exp);
    int pos = 0;

    if(validator.validate(pesel, pos) == QValidator::Invalid) {
        error = "Podany pesel jest nieprawidłowy";
        flag = false;
    }

    exp.setPattern("^[\\w'\\-,.]*[^_!¡?÷?¿\\/\\\\+=@#$%ˆ&*(){}|~<>;:[\\]]*");
    validator.setRegularExpression(exp);

    if(validator.validate(name, pos) == QValidator::Invalid || name.isEmpty()) {
        error = "Podane imię jest nieprawidłowe";
        flag = false;
    }

    if(validator.validate(surname, pos) == QValidator::Invalid || surname.isEmpty()) {
        error = "Podane nazwisko jest nieprawidłowe";
        flag = false;
    }

    exp.setPattern("^\\S+@\\S+\\.\\S+");
    validator.setRegularExpression(exp);

    if(validator.validate(email, pos) == QValidator::Invalid) {
        error = "Podany adres e-mail jest nieprawidłowy";
        flag = false;
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error);
    }

    return flag;
}
