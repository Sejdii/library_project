/**
  * @file worker.h
  * @brief Plik z klasą Worker
  */

#ifndef WORKER_H
#define WORKER_H

#include <QString>

#include <lib/user.h>

const int WORKER_DEF_TYPE = 0; /**< Stała określająca zwykłego użytkownika */
const int WORKER_ADM_TYPE = 1; /**< Stała określająca użytkownika administratora */

/**
 * @brief Klasa Worker odpowiadająca za operacje na pracownikach bazy danych
 */
class Worker : public User
{
private:
    unsigned int type; /**< Typ pracownika */
    QString name; /**< Imię pracownika */
    QString surname; /**< Nazwisko pracownika */
public:
    /**
     * @brief Konstruktor
     * @param user Obiekt użytkownik
     */
    Worker(User user);
    /**
     * @brief Konstruktor
     * @param type Typ pracownika
     * @param name Imię
     * @param surname Nazwisko
     */
    Worker(int type, QString name, QString surname);
    /**
     * @brief Konstruktor
     * @param id ID pracownika
     */
    Worker(unsigned int id);

    /**
     * @brief Przeprowadza walidacje pól klasy
     * @return Zwraca TRUE jeżeli walidacja się powiedzie lub FALSE w przeciwnym przypadku
     */
    bool validate();

    /**
     * @brief Ustawia pola klasy za pomocą obiektu z parametru
     * @param user Użytkownik
     */
    void set_user(User user);
    /**
     * @brief Ustawia pole id klasy
     * @param id ID pracownika
     */
    void set_id(unsigned int id);
    /**
     * @brief Pobiera dane o pracowniku
     */
    void fetch_worker_data();

    /**
     * @brief Zwraca wartośc pola name klasy
     * @return Imię pracownika
     */
    QString getName();

    /**
     * @brief Wprowadza dane do bazy danych z klasy
     * @return Zwraca ID nowododanego rekordu lub -1 w przypadku nie powodzenia operacji.
     */
    int push();
    /**
     * @brief Zwraca wartość pola type klasy
     * @return Typ użytkownika
     */
    int getType();
};

#endif // WORKER_H
