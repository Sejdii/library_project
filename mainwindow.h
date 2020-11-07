#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QFormLayout>
#include <QDateEdit>

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
};
#endif // MAINWINDOW_H
