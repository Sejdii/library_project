#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QtSql>
#include <QLabel>
#include <QTableView>

#include "lib/client.h" 

class ClientWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ClientWindow(unsigned int id);

    void setWindow();
    
    QHBoxLayout* getSearchBox(QString value="");
    
    QTableView* get_search_result(QString like="");

private:
    void stage_main_stage(QString like="");
    
    Client* client;
    
    QWidget* widget;
    
    QLineEdit* search_input;
    
    QTableView* search_result;
    
private slots:
    
    void search_slot();

};

#endif // CLIENTWINDOW_H
