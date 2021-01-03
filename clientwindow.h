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

class ClientWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ClientWindow(unsigned int id);

    void setWindow();
    void create_menu();
    
    QHBoxLayout* getSearchBox(QString value="");
    
    QTableView* get_search_result(QString like="");

private:
    void stage_main_stage(QString like="");
    void stage_check_availability();
    void stage_not_ended_rents();
    void stage_all_rents();
    void stage_change_password();
    
    Client* client;
    
    QWidget* widget;
    
    QLineEdit* search_input;
    QLineEdit* check_isbn;
    QLineEdit* input_change_password_old;
    QLineEdit* input_change_password_new;
    
    QTableView* search_result;
    
    QMenu* menu_tools;
    QMenu* menu_account;
    QMenu* menu_rents;
    
    QAction* action_menu_check_availability;
    QAction* action_menu_change_password;
    QAction* action_menu_logout;
    QAction* action_menu_main;
    QAction* action_menu_not_ended_rents;
    QAction* action_menu_all_rents;
    
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
