#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFormLayout>
#include <QDateEdit>
#include <QSpinBox>

#include <address.h>
#include "client.h"
#include "user.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void setWindow();
    void setStage(QString stage);

private slots:
    void loginAsClientSlot();
    void loginAsWorkerSlot();
    void registerAsClientSlot();

    void registerClientSlot();

private:
    void stage_homepage();
    void stage_login_client();
    void stage_register_client();

    void create_menu();
    void create_actions();

    QWidget *widget;

    QMenu* loginMenu;
    QMenu* registerMenu;

    QAction* loginAsClient;
    QAction* loginAsWorker;
    QAction* registerAsClient;

    QLineEdit* register_login;
    QLineEdit* register_password;
    QLineEdit* register_password_repeat;
    QLineEdit* register_pesel;
    QLineEdit* register_name;
    QLineEdit* register_surname;
    QLineEdit* register_email;
    QLineEdit* register_city;
    QLineEdit* register_post_code;
    QLineEdit* register_street;
    QSpinBox* register_house_nr;
    QLineEdit* register_flat_nr;
};
#endif // MAINWINDOW_H
