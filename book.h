#ifndef BOOK_H
#define BOOK_H

#include <qstring.h>

#include "table.h"

class Book : public Table
{
public:
    Book();
private:
    QString isbn;
    QString title;
    unsigned int publisher_id;
    unsigned int publish_year;
    QString description;
    unsigned int items_nr;
};

#endif // BOOK_H
