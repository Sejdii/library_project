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

    void stage_homepage();
    void stage_addworker();

private:
    QWidget* widget;

    QMenu* workersMenu;

    QAction* addWorker;
    QAction* scroolWorker;

    QLineEdit* register_worker_login;
    QLineEdit* register_worker_password;
    QLineEdit* register_worker_password_repeat;
    QLineEdit* register_worker_name;
    QLineEdit* register_worker_surname;

    QSpinBox* register_worker_type;

    Worker* worker;

    int w_type;

private slots:
    void addWorkerSlot();
    void scrollWorkerSlot();

    void worker_add();
};

#endif // WORKERWINDOW_H
