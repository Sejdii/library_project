#ifndef WORKERWINDOW_H
#define WORKERWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QLayout>

#include "worker.h"

class WorkerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit WorkerWindow(QWidget *parent = nullptr);

    void setWindow();
    void create_menu();
    void create_actions();
    void set_worker(unsigned int id);
    void setStage(QString stage);

    void stage_homepage();

private:
    QWidget* widget;

    QMenu* workersMenu;

    Worker* worker;

private slots:
    void addWorkerSlot();
};

#endif // WORKERWINDOW_H
