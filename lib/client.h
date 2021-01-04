/**
  * @file client.h
  * @brief Klasa Client
  */

#ifndef CLIENT_H
#define CLIENT_H

#include "lib/user.h"
#include <QString>
#include <QMessageBox>
#include <QValidator>
#include <QRegularExpression>

#include "lib/dbmanager.h"

/**
 * @brief Klasa Client
 */
class Client : public User
{
private:
    QString pesel; /**< PESEL */
    QString name; /**< Imię */
    QString surname; /**< Nazwisko */
    QString email; /**< E-mail */
    unsigned int address_id; /**< ID adresu */

public:
    /**
     * @brief Konstruktor
     * @param pesel PESEL
     * @param name Imię
     * @param surname Nazwisko
     * @param email E-mail
     */
    Client(QString pesel, QString name, QString surname, QString email);
    /**
     * @brief Konstruktor
     * @param id ID
     */
    Client(unsigned int id);

    /**
     * @brief Dokonuje walidacji pól klasy
     * @param edit Określa czy walidacja jest w stosunku do edytowania danego rekordu
     * @return Zwraca TRUE jeżeli walidacja przebiegnie pomyślnie, w przeciwnym wypadku FALSE
     */
    bool validate(bool edit=false);
    /**
     * @brief Sprawdza unikalnośc adresu E-mail
     * @return Jeżeli adres jest unikalny zwraca TRUE, w innym wypadku FALSE
     */
    bool email_unique();

    /**
     * @brief Ustawia użytkownika dla klienta
     * @param user Użytkownik
     */
    void set_user(User user);
    /**
     * @brief Ustawia pole address_id klasy
     * @param id ID adresu
     */
    void set_addr(unsigned int id);

    /**
     * @brief Wprowadza dane z klasy do bazy
     * @return Zwraca ID nowododanego pola lub -1 w przypadku brak powodzenia operacji.
     */
    int push();
    
    /**
     * @brief Pobiera dane klienta o zadanym ID
     * @param id ID klienta
     * @return zwraca TRUE jeżeli uda się pobrać dane, w przeciwnym wypadku FALSE
     */
    bool fetch_by_id(unsigned int id);
    
    /**
     * @brief Zwraca listę do completera
     * @return Lista do completera
     */
    static QStringList get_completer_list();
    
    /**
     * @brief Sprawdza czy klient o podanym id istnieje
     * @param id ID klienta
     * @return Zwraca ID klienta lub -1 jeden jeżeli klient nie zostanie znaleziony
     */
    static int is_exist(unsigned int id);
};

#endif // CLIENT_H
