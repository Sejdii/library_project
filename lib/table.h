/**
  * @file table.h
  * @brief Plik z klasą Table
  */

#ifndef TABLE_H
#define TABLE_H

/**
 * @brief Klasa Table
 */
class Table
{
public:
    /**
     * @brief Konstruktor
     */
    Table();

    /**
     * @brief Wprowadza dane do bazy danych z klasy
     * @return Zwraca ID nowododanego rekordu lub -1 w przypadku nie powodzenia operacji.
     */
    virtual int push() = 0;

    /**
     * @brief Przeprowadza walidacje pól klasy
     * @param edit Określa czy dokonujemy edycji już istniejący danych TRUE, czy dodajemy nowe dane FALSE
     * @return Zwraca TRUE jeżeli walidacja się powiedzie lub FALSE w przeciwnym przypadku
     */
    virtual bool validate(bool edit=false) = 0;
    
protected:
    unsigned int id; /**< ID rekordu */
};

#endif // TABLE_H
