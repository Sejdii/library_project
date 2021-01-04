/**
  * @file book.h
  * @brief Klasa Book
  */

#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QRegularExpression>
#include <QValidator>
#include <QtSql>
#include <QDebug>
#include <QMessageBox>

#include "lib/table.h"

/**
 * @brief Klasa Book
 */
class Book : public Table
{
public:
    /**
     * @brief Konstruktor
     * @param isbn ISBN książki
     * @param title Tytuł książki
     * @param publisher_name Nazwa wydawcy
     * @param publish_year Rok wydania
     * @param description opis
     * @param items_nr Liczba egzemplarzy
     */
    Book(QString isbn, QString title, QString publisher_name, unsigned int publish_year, QString description, unsigned int items_nr);

    bool validate(bool edit = false) override;

    int push() override;

    /**
     * @brief Sprawdza czy ISBN jest unikalny
     * @return Jeżeli ISBN jest unikalny zwraca TRUE, w innym wypadku FALSE
     */
    bool check_unique_isbn();

    /**
     * @brief Pobiera do klasy ID wydawcy
     * @return ID wydawcy, jeżeli wydawca nie zostanie znaleziony zwraca -1
     */
    int get_id_publisher();

    /**
     * @brief Tworzy połączenie na lini autor - książka
     * @param author_id ID autora
     * @return Zwraca ID autora
     */
    int make_connection_author(int author_id);
    
    /**
     * @brief Zwraca listę do completera
     * @return Lista do completera
     */
    static QStringList get_completer_list();
    
    /**
     * @brief Sprawdza czy książka o podanym ISBN istnieje
     * @param isbn ISBN książki
     * @return Jeżeli książka istnieje to zwracana jest jej wartość ID, w przeciwynym wypadku wartość -1
     */
    static int is_exist(QString isbn);
    
    /**
     * @brief Sprawdza czy książkę można wypożyczyć
     * @param id ID książki
     * @return Zwraca TRUE jeżeli książkę można wypożyczyć lub FALSE jeżeli jest to niemożliwe
     */
    static bool check_availability(unsigned int id);

private:
    QString isbn; /**< ISBN książki */
    QString title; /**< Tytuł */
    int publisher_id; /**< ID wydawcy */
    QString publisher_name; /**< Nazwa wydawcy */
    unsigned int publish_year; /**< Rok wydania */
    QString description; /**< Opis */
    unsigned int items_nr; /**< Liczba egzemplarzy */
    unsigned int author_id; /**< ID autora */
};

#endif // BOOK_H
