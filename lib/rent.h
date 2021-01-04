/**
  * @file rent.h
  * @brief Plik z klasą Rent
  */

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

/**
 * @brief Klasa Rent, obsługująca wypożyczenia w bazie danych
 */
class Rent : public Table
{
public:
    /**
     * @brief Konstruktor
     * @param book_id ID książki
     * @param worker_id ID pracownika
     * @param client_id ID klienta
     * @param start_date Data startu wypożyczenia
     * @param end_date Termin zakończenia wypożyczenia
     */
    Rent(QString book_id, unsigned int worker_id, unsigned int client_id, QString start_date, QString end_date);
    
    bool validate(bool edit = false) override;
    
    int push() override;
    
    /**
     * @brief Funkcja kończy wypożyczenie
     * @param id ID wypożyczenia
     * @return  Zwraca TRUE jeżeli operacja się powiedzie, w przeciwnym wypadku FALSE
     */
    static bool end_rent(unsigned int id);
    
private:
    int book_id; /**< ID książki */
    int worker_id; /**< ID pracownika */
    int client_id; /**< ID klienta */
    QString start_date; /**< Data początku wypożyczenia */
    QString end_date; /**< Termin końca wypożyczenia */
    QString ended; /**< Data końca wypozyczenia */
};

#endif // RENT_H
