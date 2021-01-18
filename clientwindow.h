/**
  * @file clientwindow.h
  * @brief Plik zawierający klasę okna ClientWindow
  */

#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QtSql>
#include <QLabel>
#include <QTableView>
#include <QAction>
#include <QMenuBar>

#include "lib/client.h" 
#include "lib/book.h"
#include "lib/color.h"

/**
 * @brief Klasa ClientWindow, obsługująca operacje na oknie części bazy danych poświęconej klientom
 */
class ClientWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor
     * @param id ID klienta
     */
    explicit ClientWindow(unsigned int id);

    /**
     * @brief Ustawia właściwości okna
     */
    void setWindow();
    /**
     * @brief Tworzy menu
     */
    void create_menu();
    
    /**
     * @brief Tworzy i zwraca pole wyszukiwania
     * @param value Wartość domyślna pola wyszukiwania
     * @return Pole wyszukiwania
     */
    QHBoxLayout* getSearchBox(QString value="");
    
    /**
     * @brief Zwraca rezultat wyszukiwania
     * @param like Wzorzec szukania
     * @return Zwraca tabelę z wynikami wyszukiwania
     */
    QTableView* get_search_result(QString like="");

private:
    /**
     * @brief Główna scena
     * @param like Wzorzec szukania
     */
    void stage_main_stage(QString like="");
    /**
     * @brief Scena z szukaniem dostępności książki
     */
    void stage_check_availability();
    /**
     * @brief Scena z pokazaniem nie zakończonych przez użytkownika wypożyczeń
     */
    void stage_not_ended_rents();
    /**
     * @brief Scena ze wszystkimi wypożyczeniami klienta
     */
    void stage_all_rents();
    /**
     * @brief Scena pozwalająca zmienić hasło użytkownikowi
     */
    void stage_change_password();
    
    /**
     * @brief Wskaźnik na klienta
     */
    Client* client;
    
    /**
     * @brief Główny widget okna
     */
    QWidget* widget;
    
    QLineEdit* search_input; /**< Pole pobierające wartość wyszukiwania od użytkownika */
    QLineEdit* check_isbn; /**< Pole pobierające numer isbn od użytkownika */
    QLineEdit* input_change_password_old; /**< Pole pobierające stare hasło od użytkownika  */
    QLineEdit* input_change_password_new; /**< Pole pobierające nowe hasło od użytkownika */
    
    QTableView* search_result; /**< Wynik operacji wyszukiwania */
    
    QMenu* menu_tools; /**< Element menu - narzędzia  */
    QMenu* menu_account; /**< Element menu - konto */
    QMenu* menu_rents; /**< Element menu - wypożyczenia  */
    
    QAction* action_menu_check_availability; /**< Akcja menu - sprawdź dostępność książki */
    QAction* action_menu_change_password; /**< Akcja menu - zmień hasło  */
    QAction* action_menu_logout; /**< Akcja menu - wyloguj się */
    QAction* action_menu_main; /**< Akcja menu - wyszukaj książki */
    QAction* action_menu_not_ended_rents; /**< Akcja menu - aktywne wypożyczenia */
    QAction* action_menu_all_rents; /**< Akcja menu - wszystkie wypożyczenia */
    
private slots:
    void search_slot();
    void check_availability_slot();
    void change_password_slot();
    
    void slot_menu_check_availability();
    void slot_menu_change_password();
    void slot_menu_logout();
    void slot_menu_main();
    void slot_menu_not_ended_rents();
    void slot_menu_all_rents();

};

#endif // CLIENTWINDOW_H
