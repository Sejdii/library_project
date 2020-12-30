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
#include "sqlconsole.h"

class WorkerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit WorkerWindow(unsigned int id, QWidget *parent = nullptr);

    void setWindow();
    void create_menu();
    void create_actions();
    void set_worker(unsigned int id);
    void setStage(QString stage);

    QHBoxLayout* getSearchBox();

    void stage_homepage();
    void stage_addworker();
    void stage_scrollworker();
    void stage_changepasswd();
    void stage_client_scroll();
    void stage_publisher_add();
    void stage_publisher_scroll();
    void stage_author_add();
    void stage_author_scroll();
    void stage_book_add();
    void stage_book_scroll();
    void stage_rent_add();
    void stage_rent_scroll();
    void stage_sql_console();

public slots:
    void customMenuRequested(QPoint pos);
    void customRentMenuRequested(QPoint pos);

private:
    QWidget* widget;

    QMenu* workersMenu;
    QMenu* clientsMenu;
    QMenu* booksMenu;
    QMenu* authorsMenu;
    QMenu* publisherMenu;
    QMenu* rentsMenu;
    QMenu* accountMenu;
    QMenu* databaseMenu;

    QAction* addWorker;
    QAction* scroolWorker;
    QAction* client_scroll;
    QAction* action_book_add;
    QAction* book_scroll;
    QAction* action_author_add;
    QAction* author_scroll;
    QAction* action_menu_publisher_add;
    QAction* publisher_scroll;
    QAction* action_rent_add;
    QAction* rent_scroll;
    QAction* action_database_sql_console;
    QAction* action_menu_account_logout;
    QAction* action_menu_account_change_passwd;
    QAction* action_table_menu_delete;
    QAction* action_table_menu_save;
    QAction* action_table_menu_copy_id;
    QAction* action_table_menu_rent_end;

    QLineEdit* register_worker_login;
    QLineEdit* register_worker_password;
    QLineEdit* register_worker_password_repeat;
    QLineEdit* register_worker_name;
    QLineEdit* register_worker_surname;
    QLineEdit* register_publisher_name;
    QLineEdit* register_publisher_description;
    QLineEdit* register_author_name;
    QLineEdit* register_author_surname;
    QLineEdit* register_book_isbn;
    QLineEdit* register_book_title;
    QLineEdit* register_book_description;
    QLineEdit* register_book_publisher_id;
    QLineEdit* register_book_author;
    QLineEdit* register_rent_book;
    QLineEdit* register_rent_client;
    QLineEdit* search_input;

    QSpinBox* register_worker_type;
    QSpinBox* register_book_items_nr;
    QSpinBox* register_book_year;
    
    QDateTimeEdit* register_rent_time_start;
    QDateTimeEdit* register_rent_time_end;

    QTableView* table;

    Worker* worker;

    int w_type;

    int table_row_id;
    
    int clipboard;

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
