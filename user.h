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

    void password_hash();
    void set_user(User user);

    QString getLogin();
    QString getPassword();
    unsigned int getID();
};

#endif // USER_H
