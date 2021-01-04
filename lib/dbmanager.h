/**
  * @file dbmanager.h
  * @brief Plik z klasą DBManager
  */

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>

#include "lib/worker.h"

/**
 * @brief DATABASE_PATH ścieżka do pliku bazy danych
 */
const QString DATABASE_PATH = "library.db";

/**
 * @brief Klasa DBManger do zarządzania bazą danych
 */
class DBManager
{
public:
    /**
     * @brief Konstruktor
     * @param path Ścieżka dostępu do pliku bazy danych
     */
    DBManager(const QString& path);
    /**
     * @brief Funkcja inicjująca plik bazy danych
     * @param path Ścieżka dostępu do pliku bazy danych
     * @param force Określa czy ma zostać wymuszona inicjalizacja, jeżeli TRUE to plik bazy, jeżeli tak istniał zostanie usunięty i stworzony ponownie
     * @return Zwraca TRUE jeżeli operacjia inicjalizacji się powiedzie
     */
    static bool initial_database(const QString& path, bool force=false);

    /**
     * @brief Zwraca bazę danych
     * @return Zwraca pole database z klasy
     */
    QSqlDatabase get_database();

private:
    QSqlDatabase database; /**< Obiekt bazy danych */
};

#endif // DBMANAGER_H
