#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QRegularExpression>
#include <QValidator>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

#include "lib/table.h"

class Book : public Table
{
public:
    Book(QString isbn, QString title, QString publisher_name, unsigned int publish_year, QString description, unsigned int items_nr);

    bool validate(bool edit = false) override;

    int push() override;

    bool check_unique_isbn();

    int get_id_publisher();

    int make_connection_author(int author_id);

private:
    QString isbn;
    QString title;
    int publisher_id;
    QString publisher_name;
    unsigned int publish_year;
    QString description;
    unsigned int items_nr;
};

#endif // BOOK_H
