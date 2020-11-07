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
    setMinimumSize(500, 400);
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
    if(stage == "login_client") {
        this->stage_login_client();
    }
    if(stage == "register_client") {
        this->stage_register_client();
    }
}

void MainWindow::stage_homepage()
{
    widget = new QWidget;
    setCentralWidget(widget);

    QLabel* hello_label = new QLabel(tr("<b style='font-size:24px'>Witaj w bibliotecznej bazie danych</b>"));
    hello_label->setAlignment(Qt::AlignCenter);

    QLabel* info_label = new QLabel(tr("<i>Zaloguj się lub zarejestruj, jeżeli nie posiadasz jeszcze konta aby rozpocząć korzystanie z bazy bibliotecznej</i>"));
    info_label->setAlignment(Qt::AlignCenter);

    QHBoxLayout* buttons = new QHBoxLayout;
    QPushButton* button_login = new QPushButton("&Zaloguj się", this);
    QPushButton* button_register = new QPushButton("&Zarejestruj się", this);
    connect(button_login, SIGNAL(released()), this, SLOT(loginAsClientSlot()));
    connect(button_register, SIGNAL(released()), this, SLOT(registerAsClientSlot()));
    buttons->addWidget(button_login);
    buttons->addWidget(button_register);
    buttons->setAlignment(Qt::AlignVCenter);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->addWidget(hello_label);
    layout->addWidget(info_label);
    layout->addLayout(buttons);
    widget->setLayout(layout);
}

void MainWindow::stage_login_client()
{
    setWindowTitle("Zaloguj się");

    QLabel* login_text = new QLabel(tr("<h1>Zaloguj się jako klient</h1>"));

    QLineEdit* login = new QLineEdit;
    login->setPlaceholderText("Login");

    QLineEdit* password = new QLineEdit;
    password->setPlaceholderText("Hasło");
    password->setEchoMode(QLineEdit::Password);

    QFormLayout* form = new QFormLayout;
    form->addRow(tr("&Login"), login);
    form->addRow(tr("&Hasło"), password);

    QPushButton* login_button = new QPushButton(tr("&Zaloguj się"));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(login_text);
    layout->addLayout(form);
    layout->addWidget(login_button);
    layout->setAlignment(Qt::AlignTop);

    qDeleteAll(widget->children());
    widget->setLayout(layout);
}

void MainWindow::stage_register_client()
{
    setWindowTitle("Zarejestruj się");

    QLineEdit* login = new QLineEdit;
    login->setPlaceholderText("Login");

    QLineEdit* password = new QLineEdit;
    password->setPlaceholderText("Hasło");
    password->setEchoMode(QLineEdit::Password);

    QLineEdit* password_repeat = new QLineEdit;
    password_repeat->setPlaceholderText("Powtórz hasło");
    password_repeat->setEchoMode(QLineEdit::Password);

    QLineEdit* pesel = new QLineEdit;
    pesel->setPlaceholderText("PESEL");

    QLineEdit* name = new QLineEdit;
    name->setPlaceholderText("Imię");

    QLineEdit* surname = new QLineEdit;
    surname->setPlaceholderText("Nazwisko");

    QLineEdit* city = new QLineEdit;
    city->setPlaceholderText("Miasto");

    QLineEdit* zip_code = new QLineEdit;
    zip_code->setPlaceholderText("Kod pocztowy");

    QLineEdit* street = new QLineEdit;
    street->setPlaceholderText("Ulica");

    QLineEdit* house_nr = new QLineEdit;
    house_nr->setPlaceholderText("Numer domu");

    QLineEdit* flat_nr = new QLineEdit;
    flat_nr->setPlaceholderText("Numer mieszkania");

    QFormLayout* form = new QFormLayout;
    form->addRow(tr("&Login"), login);
    form->addRow(tr("&Hasło"), password);
    form->addRow(tr("&Powtórz hasło"), password_repeat);
    form->addRow(tr("&PESEL"), pesel);
    form->addRow(tr("&Imię"), name);
    form->addRow(tr("&Nazwisko"), surname);
    form->addRow(tr("&Miasto"), city);
    form->addRow(tr("&Kod pocztowy"), zip_code);
    form->addRow(tr("&Ulica"), street);
    form->addRow(tr("&Numer domu"), house_nr);
    form->addRow(tr("&Numer mieszkania"), flat_nr);

    form->setVerticalSpacing(10);

    QPushButton* register_button = new QPushButton(tr("&Zarejestruj się"));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(form);
    layout->addWidget(register_button);
    layout->setAlignment(Qt::AlignTop);

    qDeleteAll(widget->children());
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
    MainWindow::setStage("login_client");
}

void MainWindow::loginAsWorkerSlot()
{
    qDebug() << "loginAsWorker";
}

void MainWindow::registerAsClientSlot()
{
    MainWindow::setStage("register_client");
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
