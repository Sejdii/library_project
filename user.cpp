#include "user.h"

User::User()
{

}

User::User(QString login, QString password)
{
    this->login = login;
    this->password = password;
}

bool User::validate()
{
    bool flag = true;
    QString error;

    QRegularExpression reg("^[a-zA-Z0-9]{8,16}$");
    QRegularExpressionValidator validator(reg);
    int pos = 0;

    if(validator.validate(login, pos) == QValidator::Invalid) {
        error = "Login musi składać się z conajmniej 8 a maksymalnie 16 znaków oraz tylko z liter i liczb";
        flag = false;
    }

    if(password.length() < 6) {
        error = "Hasło musi się składać z conajmniej 6 znaków";
        flag = false;
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error);
    }

    return flag;
}
