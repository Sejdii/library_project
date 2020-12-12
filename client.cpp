#include "client.h"

Client::Client(QString pesel, QString name, QString surname, QString email)
{
    this->pesel = pesel;
    this->name = name;
    this->surname = surname;
    this->email = email;
}

bool Client::validate(bool edit)
{
    bool flag = true;
    QString error;

    QRegularExpression exp("^[0-9]{11}");
    QRegularExpressionValidator validator(exp);
    int pos = 0;

    if(validator.validate(pesel, pos) == QValidator::Invalid || pesel.length() == 0 || pesel.length() != 11) {
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

    if(validator.validate(email, pos) == QValidator::Invalid || email.length() == 0) {
        error = "Podany adres e-mail jest nieprawidłowy";
        flag = false;
    }

    if(!login_unique(ACCOUNT_CLIENT) && !edit) {
        error = "Podany login jest już zajęty. Użyj innego";
        flag = false;
    }

    if(!email_unique() && !edit) {
        error = "Podany e-mail jest już w użyciu.";
        flag = false;
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error);
    }

    return flag;
}

void Client::set_user(User user)
{
    this->login = user.getLogin();
    this->password = user.getPassword();
}

int Client::push()
{
    QSqlQuery query;

    if(!query.prepare("INSERT INTO client VALUES(NULL, ?, ?, ?, ?, ?, ?, ?);")) {
        qDebug() << query.lastError();
    }
    query.addBindValue(login);
    query.addBindValue(password);
    query.addBindValue(pesel);
    query.addBindValue(name);
    query.addBindValue(surname);
    query.addBindValue(email);
    query.addBindValue(address_id);

    if(!query.exec()) {
        qDebug() << "INSERT INTO client table error:" << query.lastError();
        return -1;
    }

    id = query.lastInsertId().toInt();

    return id;
}

void Client::set_addr(unsigned int id)
{
    address_id = id;
}

bool Client::email_unique()
{
    QSqlQuery query;

    if(!query.prepare("SELECT id FROM client WHERE email = ?")) {
        qDebug() << query.lastError();
    }
    query.addBindValue(email);
    if(!query.exec()) {
        qDebug() << "Email unique error:" << query.lastError();
        return false;
    }

    if(query.first()) return false;
    return true;
}
