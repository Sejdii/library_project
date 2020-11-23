#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dbmanager.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    DBManager::initial_database(DATABASE_PATH);
    DBManager database(DATABASE_PATH);
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
    if(stage == "login_worker") {
        this->stage_login_worker();
    }
    if(stage == "register_client") {
        this->stage_register_client();
    }
}

void MainWindow::create_menu()
{
    loginMenu = menuBar()->addMenu(tr("&Zaloguj się"));
    loginMenu->addAction(loginAsClient);
    loginMenu->addAction(loginAsWorker);

    registerMenu = menuBar()->addMenu(tr("&Zarejestruj"));
    registerMenu->addAction(registerAsClient);
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

// #################################
// #             SLOTS             #
// #################################

void MainWindow::registerClientSlot()
{

    User user_data(register_login->text(), register_password->text());
    Client new_client(register_pesel->text(), register_name->text(), register_surname->text(), register_email->text());
    new_client.set_user(user_data);
    Address address_data(register_city->text(), register_post_code->text(), register_street->text(), register_house_nr->value(), register_flat_nr->value());
    if(user_data.validate()) {
        if(new_client.validate()) {
            if(address_data.validate()) {
                if(user_data.compare_passwords(register_password_repeat->text(), true)) {
                    // VALIDATION SUCCESS
                    if(address_data.push() >= 0) {
                        new_client.set_addr(address_data.getID());
                        new_client.password_hash();
                        if(new_client.push() >= 0) {
                            MainWindow::setStage("login_client");
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::loginClientSlot()
{
    User user_data(login_login->text(), login_password->text());
    user_data.password_hash();
    if(user_data.verify(ACCOUNT_CLIENT)) {
        ClientWindow* cwindow = new ClientWindow;
        cwindow->show();
    }
}

void MainWindow::loginAsClientSlot()
{
    MainWindow::setStage("login_client");
}

void MainWindow::loginAsWorkerSlot()
{
    MainWindow::setStage("login_worker");
}

void MainWindow::registerAsClientSlot()
{
    MainWindow::setStage("register_client");
}

void MainWindow::loginWorkerSlot()
{
    Worker worker(User(login_login->text(), login_password->text()));
    worker.password_hash();
    if(worker.verify(ACCOUNT_WORKER)) {
        //worker.fetch_worker_data();

        WorkerWindow* workerwindow = new WorkerWindow(worker.getID()); // CREATING NEW WINDOW - WORKER WINDOW
        workerwindow->show();
        close();
    }
}

// #################################
// #            STAGES             #
// #################################

void MainWindow::stage_login_worker()
{
    setWindowTitle("Zaloguj się");

    QLabel* login_text = new QLabel(tr("<h1>Zaloguj się jako pracownik</h1>"));

    login_login = new QLineEdit;
    login_login->setPlaceholderText("Login");

    login_password = new QLineEdit;
    login_password->setPlaceholderText("Hasło");
    login_password->setEchoMode(QLineEdit::Password);

    QFormLayout* form = new QFormLayout;
    form->addRow(tr("&Login"), login_login);
    form->addRow(tr("&Hasło"), login_password);

    QPushButton* login_button = new QPushButton(tr("&Zaloguj się"));
    connect(login_button, SIGNAL(released()), this, SLOT(loginWorkerSlot()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(login_text);
    layout->addLayout(form);
    layout->addWidget(login_button);
    layout->setAlignment(Qt::AlignTop);

    qDeleteAll(widget->children());
    widget->setLayout(layout);
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

    login_login = new QLineEdit;
    login_login->setPlaceholderText("Login");

    login_password = new QLineEdit;
    login_password->setPlaceholderText("Hasło");
    login_password->setEchoMode(QLineEdit::Password);

    QFormLayout* form = new QFormLayout;
    form->addRow(tr("&Login"), login_login);
    form->addRow(tr("&Hasło"), login_password);

    QPushButton* login_button = new QPushButton(tr("&Zaloguj się"));
    connect(login_button, SIGNAL(released()), this, SLOT(loginClientSlot()));

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

    register_login = new QLineEdit;
    register_login->setPlaceholderText("Login");

    register_password = new QLineEdit;
    register_password->setPlaceholderText("Hasło");
    register_password->setEchoMode(QLineEdit::Password);

    register_password_repeat = new QLineEdit;
    register_password_repeat->setPlaceholderText("Powtórz hasło");
    register_password_repeat->setEchoMode(QLineEdit::Password);

    register_pesel = new QLineEdit;
    register_pesel->setPlaceholderText("PESEL");

    register_name = new QLineEdit;
    register_name->setPlaceholderText("Imię");

    register_surname = new QLineEdit;
    register_surname->setPlaceholderText("Nazwisko");

    register_email = new QLineEdit;
    register_email->setPlaceholderText("Adres E-mail");

    register_city = new QLineEdit;
    register_city->setPlaceholderText("Miasto");

    register_post_code = new QLineEdit;
    register_post_code->setPlaceholderText("Kod pocztowy");

    register_street = new QLineEdit;
    register_street->setPlaceholderText("Ulica");

    register_house_nr = new QSpinBox;
    register_house_nr->setMinimum(0);
    register_house_nr->setSingleStep(1);

    register_flat_nr = new QSpinBox;
    register_flat_nr->setMinimum(0);
    register_flat_nr->setSingleStep(1);

    QFormLayout* form = new QFormLayout;
    form->addRow(tr("&Login"), register_login);
    form->addRow(tr("&Hasło"), register_password);
    form->addRow(tr("&Powtórz hasło"), register_password_repeat);
    form->addRow(tr("&PESEL"), register_pesel);
    form->addRow(tr("&Imię"), register_name);
    form->addRow(tr("&Nazwisko"), register_surname);
    form->addRow(tr("&E-mail"), register_email);

    QFormLayout* address = new QFormLayout;
    address->addRow(tr("&Miasto"), register_city);
    address->addRow(tr("&Kod pocztowy"), register_post_code);
    address->addRow(tr("&Ulica"), register_street);
    address->addRow(tr("&Numer domu"), register_house_nr);
    address->addRow(tr("&Numer mieszkania (pozostaw 0 jeżeli nie posiadasz)"), register_flat_nr);

    QHBoxLayout* forms_layout = new QHBoxLayout;
    forms_layout->addLayout(form);
    forms_layout->addLayout(address);

    QPushButton* register_button = new QPushButton(tr("&Zarejestruj się"));
    connect(register_button, SIGNAL(released()), this, SLOT(registerClientSlot()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(forms_layout);
    layout->addWidget(register_button);
    layout->setAlignment(Qt::AlignTop);

    qDeleteAll(widget->children());
    widget->setLayout(layout);
}
