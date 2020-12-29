#include "lib/book.h"

Book::Book(QString isbn, QString title, QString publisher_name, unsigned int publish_year, QString description, unsigned int items_nr)
{
    this->isbn = isbn;
    this->publish_year = publish_year;
    this->publisher_name = publisher_name;
    this->description = description;
    this->items_nr = items_nr;
    this->title = title;
}

bool Book::validate(bool edit)
{
    bool flag = true;
    QString error_text;

    QRegularExpression exp("^[0-9]{13}");
    QRegularExpressionValidator validator(exp);
    int pos = 0;

    if(validator.validate(isbn, pos) == QValidator::Invalid || isbn.length() != 13) {
        error_text = "ISBN jest niepoprawny. Musi zawierać on dokładnie 13 cyfr";
        flag = false;
    }

    if(!check_unique_isbn() && !edit) {
        error_text = "ISBN już jest przypisany do innej książki w bazie";
        flag = false;
    }

    if(get_id_publisher() == -1 && !edit) {
        error_text = "Podany wydawca nie istnieje, wpisz poprawną nazwę wydawcy";
        flag = false;
    }

    if(title.length() == 0) {
        error_text = "Tytuł nie może być pusty";
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error_text);
    }

    return flag;
}

bool Book::check_unique_isbn()
{
    QSqlQuery query;

    if(!query.prepare("SELECT id FROM book WHERE isbn=?")) {
        qDebug() << "Book check unique isbn prepere error:" << query.lastError();
        return false;
    }

    query.addBindValue(isbn);

    if(!query.exec()) {
        qDebug() << "Book check unique isbn exec error:" << query.lastError();
        return false;
    }

    if(query.first()) return false;
    return true;
}

int Book::get_id_publisher()
{
    QSqlQuery query;

    if(!query.prepare("SELECT id FROM publisher WHERE name=?")) {
        qDebug() << "Get ID publisher prepere error:" << query.lastError();
        publisher_id = -1;
        return -1;
    }

    query.addBindValue(publisher_name);

    if(!query.exec()) {
        qDebug() << "Get ID publisher exec error:" << query.lastError();
        publisher_id = -1;
        return -1;
    }

    if(query.first()) {
        publisher_id = query.value(0).toInt();
        return publisher_id;
    }

    publisher_id = -1;
    return -1;
}

int Book::push()
{
    QSqlQuery query;

    if(!query.prepare("INSERT INTO book VALUES (NULL, ?, ?, ?, ?, ?, ?, ?)")) {
        qDebug() << "Push book prepere error:" << query.lastError();
        return -1;
    }

    query.addBindValue(isbn);
    query.addBindValue(title);
    query.addBindValue(publisher_id);
    query.addBindValue(publish_year);
    query.addBindValue(description);
    query.addBindValue(items_nr);
    query.addBindValue(author_id);

    if(!query.exec()) {
        qDebug() << "Push book exec error:" << query.lastError();
        return -1;
    }

    id = query.lastInsertId().toInt();
    return id;
}

int Book::make_connection_author(int author_id)
{
    this->author_id = author_id;
    return author_id;
}

QStringList Book::get_completer_list()
{
    QSqlQuery query;
    QStringList stringlist;

    if(!query.prepare("SELECT isbn FROM book")) {
        qDebug() << "Book get completer list prepere error: " << query.lastError();
        return stringlist;
    }

    if(!query.exec()) {
        qDebug() << "Book get completer list exec error: " << query.lastError();
        return stringlist;
    }

    int field_num = query.record().indexOf("isbn");
    while(query.next()) {
        QString name = query.value(field_num).toString();
        stringlist << name;
    }

    return stringlist;
}

int Book::is_exist(QString isbn)
{
    QSqlQuery query;
    
    if(!query.prepare("SELECT id FROM book WHERE isbn=?")) {
        qDebug() << "Book is exist prepere error: " << query.lastError();
        return -1;
    }
    
    query.addBindValue(isbn);
    
    if(!query.exec()) {
        qDebug() << "Book is exist exec error: " << query.lastError();
        return -1;
    }
    
    if(!query.first()) return -1;
    return query.value(0).toInt();
}

bool Book::check_availability(unsigned int id)
{
    QSqlQuery query_count;
    
    if(!query_count.prepare("SELECT COUNT(id) FROM rent WHERE book_id=?")) {
        qDebug() << "Book check availability prepere error: " << query_count.lastError();
        return false;
    }
    
    query_count.addBindValue(id);
    
    if(!query_count.exec()) {
        qDebug() << "Book check availability exec error: " << query_count.lastError();
        return false;
    }
    
    if(!query_count.first()) {
        return false;
    }
    
    int rent_count = query_count.value(0).toInt();
    
    QSqlQuery query_items;
    
    if(!query_items.prepare("SELECT items_nr FROM book WHERE id=?")) {
        qDebug() << "Book check availability prepere error: " << query_items.lastError();
        return false;
    }
    
    query_items.addBindValue(id);
    
    if(!query_items.exec()) {
        qDebug() << "Book check availability exec error: " << query_items.lastError();
        return false;
    }
    
    if(!query_items.first()) {
        return false;
    }
    
    int items_nr = query_items.value(0).toInt();
    
    qDebug() << rent_count << " " << items_nr;
    
    if(rent_count == items_nr) {
        return false;
    }
    
    return true;
}
