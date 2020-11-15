#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>
#include <QValidator>
#include <QRegularExpression>
#include <QMessageBox>

#include "dbmanager.h"

class Address
{
private:
    int id;
    QString city;
    QString post_code;
    QString street;
    int home_nr;
    int flat_nr;
public:
    Address(QString city, QString post_code, QString street, int home_nr, int flat_nr=0);

    bool validate();

    int push();

    int getID();
};

#endif // ADDRESS_H
