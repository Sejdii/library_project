/**
  * @file author.h
  * @brief Zawiera klasę Author
  */

#ifndef AUTHOR_H
#define AUTHOR_H

#include <QString>
#include <QRegularExpression>
#include <QValidator>
#include <QMessageBox>
#include <QtSql>

#include "lib/table.h"

/**
 * @brief Klasa Author
 */
class Author : public Table
{
public:
    /**
     * @brief Konstruktor
     * @param name Imię autora
     * @param surname Nazwisko autora
     */
    Author(QString name, QString surname);
    
    int push() override;

    bool validate(bool edit=false) override;

    /**
     * @brief Zwraca listę do completera
     * @return Lista do completera
     */
    static QStringList get_completer_list();

    /**
     * @brief Zwraca ID danego pola tabeli author
     * @param Imię i nazwisko autora
     * @return ID pola w którym znajdują się dane równe zmiennej przekazywanej przez parametr lub -1 jeżeli pole nie zostanie znalezione
     */
    static int get_id(QString name);

private:
    QString name; /*< Imię autora */
    QString surname; /*< Nazwisko autora */
};

#endif // AUTHOR_H
