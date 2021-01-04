/**
  * @file user.h
  * @brief Plik z klasą User
  */

#ifndef USER_H
#define USER_H

#include <QString>
#include <QValidator>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QtSql>

const int ACCOUNT_CLIENT = 0; /**< Stała określająca typ użytkownika jako klient */
const int ACCOUNT_WORKER = 1; /**< Stała określająca typ użytkownika jak pracownik */

/**
 * @brief Klasa User, określająca operacje na użytkownikach bazy danych
 */
class User
{
protected:
    QString login; /**< Login użytkownika */
    QString password; /**< Hasło użytkownika */
    unsigned int id; /**< ID użytkownika */
public:
    /**
     * @brief Konstruktor
     */
    User();
    /**
     * @brief Konstruktor
     * @param login Login użytkownika
     * @param password Hasło użytkownika
     */
    User(QString login, QString password);

    /**
     * @brief Dokonuje walidacji pól klasy
     * @return TRUE jeżeli walidacja się powiedzie, FALSE w przeciwnymy wypadku
     */
    bool validate();
    /**
     * @brief Funkcja porównuje obecne hasło użytkownika z hasłem podanym w parametrze
     * @param password Hasło do porównania
     * @param hint Określa czy wyświetlić stosowną informacje
     * @return Zwraca TRUE jeżeli hasła są takie same, false jeżeli nie są
     */
    bool compare_passwords(QString password, bool hint=false);
    /**
     * @brief Służy do weryfikacji danych podczas logowania, sprawdza czy login i hasło jest zgodne z danymi z bazy danych
     * @param account_type Typ użytkownika
     * @return TRUE jeżeli istnieje taki użytkownik o takich danych, FALSE w przeciwnym wypadku
     */
    bool verify(int account_type);
    /**
     * @brief Sprawdza czy login użytkownika jest unikalny
     * @param account_type Typ użytkownika
     * @return Zwraca TRUE jeżeli login jest unikalny, FALSE w przeciwnym wypadku
     */
    bool login_unique(int account_type);
    /**
     * @brief Funkcja zmienia hasło użytkownika
     * @param newpassword Nowe hasło
     * @param account_type Typ użytkownika
     * @return Zwraca TRUE jeżeli zmiena się powiedzie, FALSE w przeciwnym wypadku
     */
    bool change_password(QString newpassword, int account_type);

    /**
     * @brief Ustawia pola klasy na podstawie parametru
     * @param user Użytkownik
     */
    void set_user(User user);

    /**
     * @brief Hashuje hasło, używając algorytmu Sha3_512
     * @return Zwraca hasło po operacji hashowania
     */
    QString password_hash();
    /**
     * @brief Hashuje hasło które zostało podane jako parametr za pomocą algorytmu Sha3_512
     * @param password Hasło do zahashowania
     * @return Zwraca hasło po operacji hashowania
     */
    static QString password_hash(QString password);

    /**
     * @brief Zwraca pole login z klasy
     * @return Login
     */
    QString getLogin();
    /**
     * @brief Zwraca pole password z klasy
     * @return Password
     */
    QString getPassword();
    /**
     * @brief Zwraca nazwę typu użytkownika
     * @param account_type Typ użytkownika
     * @return Nazwa typu użytkownika
     */
    QString getTypeName(int account_type);

    /**
     * @brief Zwraca pole ID z klasy
     * @return ID
     */
    unsigned int getID();
};

#endif // USER_H
