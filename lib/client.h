#ifndef CLIENT_H
#define CLIENT_H

#include "lib/user.h"
#include <QString>
#include <QMessageBox>
#include <QValidator>
#include <QRegularExpression>

#include "lib/dbmanager.h"

class Client : public User
{
private:
    QString pesel;
    QString name;
    QString surname;
    QString email;
    unsigned int address_id;

public:
    Client(QString pesel, QString name, QString surname, QString email);

    bool validate(bool edit=false);
    bool email_unique();

    void set_user(User user);
    void set_addr(unsigned int id);

    int push();
};

#endif // CLIENT_H
