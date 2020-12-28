#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QRegularExpression>
#include <QValidator>
#include <QMessageBox>
#include <QtSql>

#include "lib/table.h"

class Author : public Table
{
public:
    Author(QString name, QString surname);

    int push() override;

    bool validate(bool edit=false) override;

    static QStringList get_completer_list();

    static int get_id(QString name);

private:
    QString name;
    QString surname;
};

#endif // AUTHOR_H
