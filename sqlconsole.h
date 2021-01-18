/**
  * @file sqlconsole.h
  * @brief Plik z klasą okna SqlConsole
  */

#ifndef SQLCONSOLE_H
#define SQLCONSOLE_H

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QtSql>
#include <QTableView>
#include <QPushButton>

#include <lib/color.h>

/**
 * @brief Klasa SqlConsole odpowiadająca za wyświetlanie oraz obsługę okna konsoli SQL
 */
class SqlConsole : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor
     * @param parent Rodzic okna
     */
    explicit SqlConsole(QWidget *parent = nullptr);
    
    /**
     * @brief Ustawia właściwości okna
     */
    void set_window();
    
private:
    /**
     * @brief Główna scena okna
     */
    void stage_main();
    /**
     * @brief Główny widget okna
     */
    QWidget* widget;
    
    QLineEdit* query_text; /**< Pole umożliwiające wprowadzenie zapytania sql przez użytkownika */
    
    QTableView* table; /**< Tabela */
    
private slots:
    void onsubmit();
    
};

#endif // SQLCONSOLE_H
