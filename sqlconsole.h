#ifndef SQLCONSOLE_H
#define SQLCONSOLE_H

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QtSql>
#include <QTableView>
#include <QPushButton>

class SqlConsole : public QMainWindow
{
    Q_OBJECT
public:
    explicit SqlConsole(QWidget *parent = nullptr);
    
    void set_window();
    
private:
    
    void stage_main();
    
    QWidget* widget;
    
    QLineEdit* query_text;
    
    QTableView* table;
    
private slots:
    
    void onsubmit();
    
};

#endif // SQLCONSOLE_H
