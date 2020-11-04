#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void create_menu();
    void create_actions();

    QMenu* loginMenu;
    QMenu* registerMenu;

    QAction* loginAsClient;
    QAction* loginAsWorker;
    QAction* registerAsClient;
};
#endif // MAINWINDOW_H
