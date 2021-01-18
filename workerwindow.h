/**
  * @file workerwindow.h
  * @brief Plik z klasą WorkerWindow
  */

#ifndef WORKERWINDOW_H
#define WORKERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QCompleter>
#include <QTreeView>
#include <QClipboard>
#include <QGuiApplication>
#include <QDateTimeEdit>

#include "lib/worker.h"
#include "lib/client.h"
#include "lib/publisher.h"
#include "lib/author.h"
#include "lib/book.h"
#include "lib/rent.h"
#include "lib/color.h"
#include "sqlconsole.h"

/**
 * @brief Klasa WorkerWindow odpowiadająca za wyświetlanie oraz obsługę części dla pracownika
 */
class WorkerWindow : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor
     * @param id ID pracownika
     * @param parent Wskaźnik na rodzica
     */
    explicit WorkerWindow(unsigned int id, QWidget *parent = nullptr);

    /**
     * @brief Ustawia właściwości okna
     */
    void setWindow();
    /**
     * @brief Tworzy menu
     */
    void create_menu();
    /**
     * @brief Tworzy akcje menu
     */
    void create_actions();
    /**
     * @brief Ustawia dane pracownika
     * @param id ID pracownika
     */
    void set_worker(unsigned int id);
    /**
     * @brief Zmienia scenę okna
     * @param stage Scena
     */
    void setStage(QString stage);

    /**
     * @brief Tworzy i zwraca pole wyszukiwania
     * @return Pole wyszukiwania
     */
    QHBoxLayout* getSearchBox();

    /**
     * @brief Scena główna
     */
    void stage_homepage();
    /**
     * @brief Scena dodaj pracownika
     */
    void stage_addworker();
    /**
     * @brief Scena przeglądaj pracowników
     */
    void stage_scrollworker();
    /**
     * @brief Scena zmień hasło
     */
    void stage_changepasswd();
    /**
     * @brief Scena przeglądaj klientów
     */
    void stage_client_scroll();
    /**
     * @brief Scena dodaj wydawce
     */
    void stage_publisher_add();
    /**
     * @brief Scena przeglądaj wydawców
     */
    void stage_publisher_scroll();
    /**
     * @brief Scena dodaj autora
     */
    void stage_author_add();
    /**
     * @brief Scena przeglądaj autorów
     */
    void stage_author_scroll();
    /**
     * @brief Scena dodaj książkę
     */
    void stage_book_add();
    /**
     * @brief Scena przeglądaj książki
     */
    void stage_book_scroll();
    /**
     * @brief Scena dodaj wypożyczenie
     */
    void stage_rent_add();
    /**
     * @brief Scena przeglądaj wypożyczenia
     */
    void stage_rent_scroll();
    void stage_sql_console();

public slots:
    void customMenuRequested(QPoint pos);
    void customRentMenuRequested(QPoint pos);

private:
    QWidget* widget; /**< Główny widget */

    QMenu* workersMenu; /**< Menu - pracownicy */
    QMenu* clientsMenu; /**< Menu - klienci */
    QMenu* booksMenu; /**< Menu - książki */
    QMenu* authorsMenu; /**< Menu - autorzy */
    QMenu* publisherMenu; /**< Menu - wydawcy */
    QMenu* rentsMenu; /**< Menu - wypożyczenia */
    QMenu* accountMenu; /**< Menu - konto */
    QMenu* databaseMenu; /**< Menu - baza */

    QAction* addWorker; /**< Akcja menu - dodaj pracownika */
    QAction* scroolWorker; /**< Akcja menu - przeglądaj pracowników */
    QAction* client_scroll; /**< Akcja menu - przeglądaj klientów */
    QAction* action_book_add; /**< Akcja menu - dodaj książkę */
    QAction* book_scroll; /**< Akcja menu - przeglądaj książki */
    QAction* action_author_add; /**< Akcja menu - dodaj autora */
    QAction* author_scroll; /**< Akcja menu - przeglądaj autorów */
    QAction* action_menu_publisher_add; /**< Akcja menu - dodaj wydawcę */
    QAction* publisher_scroll; /**< Akcja menu - przeglądaj wydawców */
    QAction* action_rent_add; /**< Akcja menu - dodaj wypożyczenie */
    QAction* rent_scroll; /**< Akcja menu - przeglądaj wypożyczenia */
    QAction* action_database_sql_console; /**< Akcja menu - konsola sql */
    QAction* action_menu_account_logout; /**< Akcja menu - wyloguj się */
    QAction* action_menu_account_change_passwd; /**< Akcja menu - zmień hasło */
    QAction* action_table_menu_delete; /**< Akcja tabeli - usuń */
    QAction* action_table_menu_save; /**< Akcja tabeli - zapisz */
    QAction* action_table_menu_copy_id; /**< Akcja tabeli - kopiuj id */
    QAction* action_table_menu_rent_end; /**< Akcja tabeli - zakończ wypożyczenie */

    QLineEdit* register_worker_login; /**< Pole pozwalające użytkownikowi wprowdzić login */
    QLineEdit* register_worker_password; /**< Pole pozwalające użytkownikowi wprowdzić hasło */
    QLineEdit* register_worker_password_repeat; /**< Pole pozwalające użytkownikowi wprowdzić powtórzenie hasła */
    QLineEdit* register_worker_name; /**< Pole pozwalające użytkownikowi wprowdzić imię */
    QLineEdit* register_worker_surname; /**< Pole pozwalające użytkownikowi wprowdzić nazwisko */
    QLineEdit* register_publisher_name; /**< Pole pozwalające użytkownikowi wprowdzić nazwę wydawcy */
    QLineEdit* register_publisher_description; /**< Pole pozwalające użytkownikowi wprowdzić opis */
    QLineEdit* register_author_name; /**< Pole pozwalające użytkownikowi wprowdzić imię autora */
    QLineEdit* register_author_surname; /**< Pole pozwalające użytkownikowi wprowdzić nazwisko autora */
    QLineEdit* register_book_isbn; /**< Pole pozwalające użytkownikowi wprowdzić isbn */
    QLineEdit* register_book_title; /**< Pole pozwalające użytkownikowi wprowdzić tytuł książki */
    QLineEdit* register_book_description; /**< Pole pozwalające użytkownikowi wprowdzić opis książki */
    QLineEdit* register_book_publisher_id; /**< Pole pozwalające użytkownikowi wprowdzić ID wydawcy */
    QLineEdit* register_book_author; /**< Pole pozwalające użytkownikowi wprowdzić autora książki */
    QLineEdit* register_rent_book; /**< Pole pozwalające użytkownikowi wprowdzić nazwę książki */
    QLineEdit* register_rent_client; /**< Pole pozwalające użytkownikowi wprowdzić kod klienta */
    QLineEdit* search_input; /**< Pole pozwalające użytkownikowi wprowdzić tekst do wyszukania */

    QSpinBox* register_worker_type; /**< Pole pozwalające użytkownikowi wprowdzić typ pracownika */
    QSpinBox* register_book_items_nr; /**< Pole pozwalające użytkownikowi wprowdzić liczbę egzemplarzy książki */
    QSpinBox* register_book_year; /**< Pole pozwalające użytkownikowi wprowdzić rok publikacji */
    
    QDateTimeEdit* register_rent_time_start; /**< Pole pozwalające użytkownikowi wprowdzić datę początku wypożyczenia */
    QDateTimeEdit* register_rent_time_end; /**< Pole pozwalające użytkownikowi wprowdzić datę końca wypożyczenia */

    QTableView* table; /**< Tabela */

    Worker* worker; /**< Pracownik */

    int w_type; /**< Typ pracownika */

    int table_row_id; /**< ID wiersza w tabeli */
    
    int clipboard; /**< Schowek */

private slots:
    void addWorkerSlot();
    void scrollWorkerSlot();
    void client_scrollSlot();
    void book_addSlot();
    void book_scrollSlot();
    void author_addSlot();
    void author_scrollSlot();
    void publisher_addSlot();
    void publisher_scrollSlot();
    void rent_addSlot();
    void rent_scrollSlot();
    void account_changepasswdSlot();
    void account_logoutSlot();
    void database_sql_consoleSlot();

    void worker_add();
    void account_changepasswd();
    void publisher_add();
    void author_add();
    void book_add();
    void rent_add();

    void search_slot();
    void delete_slot();
    void save_slot();
    void copy_id_slot();
    void end_rent_slot();
    void table_on_change();
};

#endif // WORKERWINDOW_H
