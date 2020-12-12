#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QRegularExpression>
#include <QValidator>
#include <QMessageBox>
#include <QtSql>

#include "table.h"

class Author : public Table
{
public:
    Author(QString name, QString surname);

    int push() override;

    bool validate() override;
private:
    QString name;
    QString surname;
};

#endif // AUTHOR_H
