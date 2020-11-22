#include "workerwindow.h"

WorkerWindow::WorkerWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindow();
    widget = new QWidget;
    setCentralWidget(widget);
    create_menu();
    qDebug() << worker->getName();

    //setStage("homepage");
}

void WorkerWindow::setWindow()
{
    setMinimumSize(500, 400);
    resize(800, 600);
    setWindowTitle("Witaj pracowniku");
}

void WorkerWindow::create_menu()
{
    workersMenu = menuBar()->addMenu(tr("&Zaloguj się"));
}

void WorkerWindow::create_actions()
{

}

void WorkerWindow::set_worker(unsigned int id)
{
    qDebug() << id;
    worker = new Worker(id);
    worker->fetch_worker_data();
}

void WorkerWindow::setStage(QString stage)
{
    if(stage == "homepage") {
        stage_homepage();
    }
}

// #################################
// #             SLOTS             #
// #################################

void WorkerWindow::addWorkerSlot()
{
    qDebug() << "addWorkerSlot";
}

// #################################
// #            STAGES             #
// #################################

void WorkerWindow::stage_homepage()
{
    QLabel* hello_label = new QLabel(QString("Witaj %1").arg(worker->getName()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(hello_label);

    widget->setLayout(layout);
}
