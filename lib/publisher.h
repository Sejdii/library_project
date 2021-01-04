/**
  * @file publisher.h
  * @brief Plik z klasą Publisher
  */

#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QString>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

#include "lib/table.h"

/**
 * @brief Klasa Publisher
 */
class Publisher : public Table
{
public:
    /**
     * @brief Konstruktor
     * @param name Nazwa wydawcy
     * @param description Opis wydawcy
     */
    Publisher(QString name, QString description);

    bool validate(bool edit=false) override;
    
    /**
     * @brief Sprawdza czy nazwa wydawcy jest unikalna
     * @return Zwraca TRUE jeżeli jest unikalna, w przeciwnym wypadku FALSE
     */
    bool check_name_unique();

    int push() override;

    /**
     * @brief Zwraca listę do completera
     * @return Lista do completera
     */
    static QStringList get_completer_list();

private:
    QString name; /**< Nazwa wydawcy */
    QString description; /**< Opis wydawcy */
};

#endif // PUBLISHER_H
