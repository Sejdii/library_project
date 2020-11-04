#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dbmanager.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    DBManager::initial_database(DATABASE_PATH);
    this->setWindow();
    this->setStage("homepage");
}

void MainWindow::setWindow()
{
    setMinimumSize(400, 300);
    resize(800, 600);
    setWindowTitle("Baza danych biblioteki");

    this->create_actions();
    this->create_menu();
}

void MainWindow::setStage(QString stage)
{
    if(stage == "homepage") {
        this->stage_homepage();
    }
}

void MainWindow::stage_homepage()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QLabel* hello_label = new QLabel(tr("<b style='font-size:24px'>Witaj w bibliotecznej bazie danych</b>"));
    hello_label->setAlignment(Qt::AlignCenter);

    QLabel* info_label = new QLabel(tr("<i>Zaloguj się lub zarejestruj, jeżeli nie posiadasz jeszcze konta aby rozpocząć korzystanie z bazy bibliotecznej</i>"));
    info_label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(hello_label);
    layout->addWidget(info_label);

    widget->setLayout(layout);

}

void MainWindow::create_menu()
{
    loginMenu = menuBar()->addMenu(tr("&Zaloguj się"));
    loginMenu->addAction(loginAsClient);
    loginMenu->addAction(loginAsWorker);

    registerMenu = menuBar()->addMenu(tr("&Zarejestruj"));
    registerMenu->addAction(registerAsClient);
}

void MainWindow::loginAsClientSlot()
{
    qDebug() << "loginAsClient";
}

void MainWindow::loginAsWorkerSlot()
{
    qDebug() << "loginAsWorker";
}

void MainWindow::registerAsClientSlot()
{
    qDebug() << "registerAsClient";
}

void MainWindow::create_actions()
{
    loginAsClient = new QAction(tr("&Jako klient"), this);
    connect(loginAsClient, &QAction::triggered, this, &MainWindow::loginAsClientSlot);

    loginAsWorker = new QAction(tr("&Jako pracownik"), this);
    connect(loginAsWorker, &QAction::triggered, this, &MainWindow::loginAsWorkerSlot);

    registerAsClient = new QAction(tr("&Konto klienta"), this);
    connect(registerAsClient, &QAction::triggered, this, &MainWindow::registerAsClientSlot);
}
