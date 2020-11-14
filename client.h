#ifndef CLIENT_H
#define CLIENT_H

#include "user.h"
#include <QString>
#include <QMessageBox>
#include <QValidator>
#include <QRegularExpression>

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

    bool validate();
};

#endif // CLIENT_H
