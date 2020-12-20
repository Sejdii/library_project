#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QString>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

#include "table.h"

class Publisher : public Table
{
public:
    Publisher(QString name, QString description);

    bool validate(bool edit=false) override;
    bool check_name_unique();

    int push() override;

    static QStringList get_completer_list();

private:
    QString name;
    QString description;
};

#endif // PUBLISHER_H
