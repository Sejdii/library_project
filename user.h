#ifndef USER_H
#define USER_H

#include <QString>
#include <QValidator>
#include <QMessageBox>
#include <QCryptographicHash>

class User
{
protected:
    QString login;
    QString password;
    unsigned int id;
public:
    User();
    User(QString login, QString password);

    bool validate();
    bool compare_passwords(QString password, bool hint=false);

    void password_hash();

    QString getLogin();
    QString getPassword();
};

#endif // USER_H
