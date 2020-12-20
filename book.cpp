#include "book.h"

Book::Book(QString isbn, QString title, unsigned int publisher_id, unsigned int publish_year, QString description, unsigned int items_nr)
{
    this->isbn = isbn;
    this->publisher_id = publisher_id;
    this->publish_year = publish_year;
    this->description = description;
    this->items_nr = items_nr;
    this->title = title;
}
