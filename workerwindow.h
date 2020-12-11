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

#include "worker.h"

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

public slots:
    void customMenuRequested(QPoint pos);

private:
    QWidget* widget;

    QMenu* workersMenu;
    QMenu* clientsMenu;
    QMenu* booksMenu;
    QMenu* authorsMenu;
    QMenu* publisherMenu;
    QMenu* rentsMenu;
    QMenu* accountMenu;

    QAction* addWorker;
    QAction* scroolWorker;
    QAction* client_scroll;
    QAction* book_add;
    QAction* book_scroll;
    QAction* author_add;
    QAction* author_scroll;
    QAction* publisher_add;
    QAction* publisher_scroll;
    QAction* rent_add;
    QAction* rent_scroll;
    QAction* action_menu_account_logout;
    QAction* action_menu_account_change_passwd;
    QAction* action_table_menu_delete;
    QAction* action_table_menu_save;

    QLineEdit* register_worker_login;
    QLineEdit* register_worker_password;
    QLineEdit* register_worker_password_repeat;
    QLineEdit* register_worker_name;
    QLineEdit* register_worker_surname;
    QLineEdit* search_input;

    QSpinBox* register_worker_type;

    QTableView* table;

    Worker* worker;

    int w_type;

    int table_row_id;

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

    void worker_add();
    void account_changepasswd();

    void search_slot();
    void delete_slot();
    void save_slot();
    void table_on_change();
};

#endif // WORKERWINDOW_H
