#ifndef USER_H
#define USER_H

#include <QString>
#include <QValidator>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QtSql>

const int ACCOUNT_CLIENT = 0;
const int ACCOUNT_WORKER = 1;

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
    bool verify(int account_type);
    bool login_unique(int account_type);
    bool change_password(QString newpassword, int account_type);

    void set_user(User user);

    QString password_hash();
    static QString password_hash(QString);

    QString getLogin();
    QString getPassword();
    QString getTypeName(int account_type);

    unsigned int getID();
};

#endif // USER_H
