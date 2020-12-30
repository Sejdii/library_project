#ifndef RENT_H
#define RENT_H

#include "lib/table.h"

#include <QString>
#include <QStringList>
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>

#include "lib/book.h"
#include "lib/client.h"

class Rent : public Table
{
public:
    Rent(QString book_id, unsigned int worker_id, unsigned int client_id, QString start_date, QString end_date);
    
    bool validate(bool edit = false) override;
    
    int push() override;
    
    static bool end_rent(unsigned int id);
    
private:
    int book_id;
    int worker_id;
    int client_id;
    QString start_date;
    QString end_date;
    QString ended;
};

#endif // RENT_H
