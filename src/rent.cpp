#include "../lib/rent.h"

Rent::Rent(QString book_id, unsigned int worker_id, unsigned int client_id, QString start_date, QString end_date)
{
    this->book_id = Book::is_exist(book_id);
    this->worker_id = worker_id;
    this->client_id = client_id;
    this->start_date = start_date;
    this->end_date = end_date;
}

bool Rent::validate(bool edit)
{
    QString error_text;
    bool flag = true;
    
    if(!Book::check_availability(book_id)) {
        error_text = "Książki nie można obecnie wypożyczyć";
        flag = false;
    }
    
    if(book_id == -1) {
        error_text = "Książka o podanym ISBN nie istnieje"; 
        flag = false;
    }
    
    if(Client::is_exist(client_id) == -1) {
        error_text = "Klient o podanym identyfikatorze nie istnieje"; 
        flag = false;
    }
    
    if(edit) NULL;
    
    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Nieprawidłowe dane", error_text);
    }
    
    return flag;
}

int Rent::push()
{
    QSqlQuery query;
    
    if(!query.prepare("INSERT INTO rent VALUES(NULL, ?, ?, ?, ?, ?, NULL)")) {
        qDebug() << "Rent push prepere error: " << query.lastError();
        return -1;
    }
    
    query.addBindValue(book_id);
    query.addBindValue(worker_id);
    query.addBindValue(client_id);
    query.addBindValue(start_date);
    query.addBindValue(end_date);
    
    if(!query.exec()) {
        qDebug() << "Rent push exec error: " << query.lastError();
        return -1;
    }
    
    return query.lastInsertId().toInt();
}

bool Rent::end_rent(unsigned int id)
{
    QSqlQuery query;
    
    if(!query.prepare("UPDATE rent SET ended=? WHERE id=?")) {
        qDebug() << "Rent end rent prepere error: " << query.lastError();
        return false;
    }
    
    query.addBindValue(QDate::currentDate().toString());
    query.addBindValue(id);
    
    if(!query.exec()) {
        qDebug() << "Rent end rent exec error: " << query.lastError();
        return false;
    }
    
    return true;
}
