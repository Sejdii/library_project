#ifndef USER_H
#define USER_H

#include <QString>
#include <QValidator>
#include <QMessageBox>

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
};

#endif // USER_H
