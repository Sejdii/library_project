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
    Client(unsigned int id);

    bool validate(bool edit=false);
    bool email_unique();

    void set_user(User user);
    void set_addr(unsigned int id);

    int push();
    
    bool fetch_by_id(unsigned int id);
    
    static QStringList get_completer_list();
    
    static int is_exist(unsigned int id);
};

#endif // CLIENT_H
