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

    if(validator.validate(login, pos) == QValidator::Invalid || login.length() == 0) {
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

QString User::getLogin()
{
    return this->login;
}

QString User::getPassword()
{
    return this->password;
}

bool User::compare_passwords(QString password, bool hint)
{
    if(this->password != password) {
        if(hint) {
            QMessageBox hintw;
            hintw.warning(nullptr, "Nieprawidłowe dane", "Podane hasła nie są takie same.");
        }
        return false;
    }
    return true;
}

void User::password_hash()
{
    password = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Sha3_512);
}

bool User::verify(int account_type)
{
    QSqlQuery query;
    QString type = "client";
    if(account_type == ACCOUNT_CLIENT) type = "client";
    else if(account_type == ACCOUNT_WORKER) type = "worker";
    if(!query.prepare(QString("SELECT id FROM %1 WHERE login = ? AND password = ?").arg(type))) qDebug() << query.lastError();
    query.addBindValue(login);
    query.addBindValue(password);
    if(!query.exec()) {
        qDebug() << "Login verify error:" << query.lastError();
        return false;
    }
    if(query.first()) return true;
    else {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane logowania", "Nieprawidłowy login lub hasło. Spróbuj ponownie.");
        return false;
    }

    return false;
}
