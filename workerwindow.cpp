#include "workerwindow.h"

WorkerWindow::WorkerWindow(unsigned int id, QWidget *parent) : QMainWindow(parent)
{
    setWindow();
    widget = new QWidget;
    setCentralWidget(widget);
    set_worker(id);

    setStage("homepage");
}

void WorkerWindow::setWindow()
{
    setMinimumSize(500, 400);
    resize(800, 600);
    setWindowTitle("Witaj pracowniku");

    create_actions();
    create_menu();
}

void WorkerWindow::create_menu()
{
    workersMenu = menuBar()->addMenu(tr("&Pracownicy"));
    workersMenu->addAction(addWorker);
    workersMenu->addAction(scroolWorker);
}

void WorkerWindow::create_actions()
{
    addWorker = new QAction(tr("&Dodaj pracownika"), this);
    connect(addWorker, &QAction::triggered, this, &WorkerWindow::addWorkerSlot);

    scroolWorker = new QAction(tr("&Przeglądaj pracowników"), this);
    connect(scroolWorker, &QAction::triggered, this, &WorkerWindow::scrollWorkerSlot);
}

void WorkerWindow::set_worker(unsigned int id)
{
    worker = new Worker(id);
    worker->fetch_worker_data();
    w_type = worker->getType();
}

void WorkerWindow::setStage(QString stage)
{
    if(stage == "homepage") {
        stage_homepage();
    }

    if(stage == "addworker") {
        stage_addworker();
    }
}

// #################################
// #             SLOTS             #
// #################################

void WorkerWindow::addWorkerSlot()
{
    setStage("addworker");
}

void WorkerWindow::scrollWorkerSlot()
{
    qDebug() << "scrollWorkerSlot";
}

void WorkerWindow::worker_add()
{
    User new_user(register_worker_login->text(), register_worker_password->text());
    Worker new_worker(register_worker_type->value() ,register_worker_name->text(), register_worker_surname->text());
    new_worker.set_user(new_user);

    if(new_user.validate()) {
        if(new_worker.validate()) {
            if(new_user.compare_passwords(register_worker_password_repeat->text(), true)) {
                // VALIDATION SUCCESS
                new_worker.password_hash();
                if(new_worker.push() >= 0) {
                    setStage("home");
                }
            }
        }
    }
}

// #################################
// #            STAGES             #
// #################################

void WorkerWindow::stage_homepage()
{
    QLabel* hello_label = new QLabel(QString("<h1>Witaj <b>%1</b></h1>").arg(worker->getName()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(hello_label);

    widget->setLayout(layout);
}

void WorkerWindow::stage_addworker()
{
    QLabel* label = new QLabel("Dodaj nowego pracownika");

    register_worker_login = new QLineEdit;
    register_worker_login->setPlaceholderText("Login pracownika");

    register_worker_password = new QLineEdit;
    register_worker_password->setEchoMode(QLineEdit::Password);
    register_worker_password->setPlaceholderText("Hasło pracownika");

    register_worker_password_repeat = new QLineEdit;
    register_worker_password_repeat->setEchoMode(QLineEdit::Password);
    register_worker_password_repeat->setPlaceholderText("Powtórz hasło pracownika");

    register_worker_type = new QSpinBox;
    register_worker_type->setMinimum(0);
    register_worker_type->setMaximum(1);
    register_worker_type->setSingleStep(1);

    register_worker_name = new QLineEdit;
    register_worker_name->setPlaceholderText("Imię pracownika");

    register_worker_surname = new QLineEdit;
    register_worker_surname->setPlaceholderText("Nazwisko pracownika");

    QFormLayout* form = new QFormLayout;
    form->addRow(tr("&Login"), register_worker_login);
    form->addRow(tr("&Hasło"), register_worker_password);
    form->addRow(tr("&Powtórz hasło"), register_worker_password_repeat);
    form->addRow(tr("&Typ użytkownika (0 - zwykły, 1 - administrator)"), register_worker_type);
    form->addRow(tr("&Imię"), register_worker_name);
    form->addRow(tr("&Nazwisko"), register_worker_surname);

    QPushButton* register_button = new QPushButton(tr("&Dodaj użytkownika"));
    connect(register_button, SIGNAL(released()), this, SLOT(worker_add()));


    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addLayout(form);
    layout->addWidget(register_button);
    layout->setAlignment(Qt::AlignTop);

    qDeleteAll(widget->children());
    widget->setLayout(layout);
}
