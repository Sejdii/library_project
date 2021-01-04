/**
  *@file address.h
  *@brief Plik klasy Address
  */

#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>
#include <QValidator>
#include <QRegularExpression>
#include <QMessageBox>

#include "lib/dbmanager.h"

/**
 * @brief Klasa Address, służąca do obsługi tabeli address bazy danych
 */
class Address
{
private:
    int id; /**< ID rekordu */
    QString city; /**< Miasto */
    QString post_code; /**< Kod pocztowy */
    QString street; /**< Ulica */
    int home_nr; /**< Numer domu */
    int flat_nr; /**< Numer mieszkania */
public:
    /**
     * @brief Konstruktor
     * @param city Miasto
     * @param post_code Kod pocztowy
     * @param street Ulicy
     * @param home_nr Numer domu
     * @param flat_nr Numer mieszkania
     */
    Address(QString city, QString post_code, QString street, int home_nr, int flat_nr=0);

    /**
     * @brief Walidacja pól klasy
     * @return Zwraca TRUE jeżeli wszystkie pola są poprawne lub FALSE jeżeli co najmniej jedeno pole nie spełniło wymagań walidacji
     */
    bool validate();

    /**
     * @brief Wstawia dane z klasy to bazy danych
     * @return Zwraca ID nowowstawionego elementu lub -1 jeżeli wstawianie się nie powiodło
     */
    int push();

    /**
     * @brief Zwraca wartość pola ID klasy
     * @return Wartość pola ID klasy
     */
    int getID();
};

#endif // ADDRESS_H
