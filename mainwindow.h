/**
  * @file mainwindow.h
  * @brief Plik z klasą okna MainWindow
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFormLayout>
#include <QDateEdit>
#include <QSpinBox>
#include <QShortcut>

#include <lib/address.h>
#include "lib/client.h"
#include "lib/user.h"
#include "clientwindow.h"
#include "workerwindow.h"

/**
 * @brief Klasa MainWindow, odpowiadająca za wyświetlanie i obsługiwanie głównego okna programu
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param parent Rodzic okna
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Ustawia właściwości okna
     */
    void setWindow();
    /**
     * @brief Ustawia scene okna
     * @param stage Scena
     */
    void setStage(QString stage);

private slots:
    void loginAsClientSlot();
    void loginAsWorkerSlot();
    void registerAsClientSlot();

    void registerClientSlot();
    void loginClientSlot();
    void loginWorkerSlot();

private:
    /**
     * @brief Scena główna okna
     */
    void stage_homepage();
    /**
     * @brief Scena logowania jako klient
     */
    void stage_login_client();
    /**
     * @brief Scena rejestracji nowego klienta
     */
    void stage_register_client();
    /**
     * @brief Scena logowania jako pracownik
     */
    void stage_login_worker();

    /**
     * @brief Tworzy menu okna
     */
    void create_menu();
    /**
     * @brief Tworzy akcje menu
     */
    void create_actions();

    QWidget *widget; /**< Główny widget okna  */

    QMenu* loginMenu; /**< Menu - zaloguj się */
    QMenu* registerMenu; /**< Menu - zarejestruj się */

    QAction* loginAsClient; /**< Akcja menu - zaloguj się jako klient */
    QAction* loginAsWorker; /**< Akcja menu - zaloguj się jako pracownik */
    QAction* registerAsClient; /**< Akcja menu - zarejestruj się */

    QLineEdit* register_login; /**< Pole umożliwiające wprowadzenie loginu przez użytkownika */
    QLineEdit* register_password; /**< Pole umożliwiające wprowadzenie hasła przez użytkownika */
    QLineEdit* register_password_repeat; /**< Pole umożliwiające wprowadzenie powtórzenia hasła przez użytkownika */
    QLineEdit* register_pesel; /**< Pole umożliwiające wprowadzenie numeru pesel przez użytkownika */
    QLineEdit* register_name; /**< Pole umożliwiające wprowadzenie imienia przez użytkownika */
    QLineEdit* register_surname; /**< Pole umożliwiające wprowadzenie nazwiska przez użytkownika */
    QLineEdit* register_email; /**< Pole umożliwiające wprowadzenie adresu e-mail przez użytkownika */
    QLineEdit* register_city; /**< Pole umożliwiające wprowadzenie miast przez użytkownika */
    QLineEdit* register_post_code; /**< Pole umożliwiające wprowadzenie numeru pocztowego przez użytkownika */
    QLineEdit* register_street; /**< Pole umożliwiające wprowadzenie ulicy przez użytkownika */
    QSpinBox* register_house_nr; /**< Pole umożliwiające wprowadzenie numeru domu przez użytkownika */
    QSpinBox* register_flat_nr; /**< Pole umożliwiające wprowadzenie numeru mieszkania przez użytkownika */

    QLineEdit* login_login; /**< Pole umożliwiające wprowadzenie loginu przez użytkownika */
    QLineEdit* login_password; /**< Pole umożliwiające wprowadzenie hasła przez użytkownika */
};
#endif // MAINWINDOW_H
