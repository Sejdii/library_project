#include "workerwindow.h"

WorkerWindow::WorkerWindow(unsigned int id, QWidget *parent) : QMainWindow(parent)
{
    set_worker(id);
    setWindow();
    widget = new QWidget;
    setCentralWidget(widget);

    setStage("homepage");
}

void WorkerWindow::setWindow()
{
    setMinimumSize(500, 400);
    resize(800, 600);
    setWindowTitle("Baza danych biblioteki - zalogowano jako pracownik");

    create_actions();
    create_menu();
}

void WorkerWindow::create_menu()
{
    if(w_type == WORKER_ADM_TYPE) { // ONLY FOR ADMIN
        workersMenu = menuBar()->addMenu(tr("&Pracownicy"));
        workersMenu->addAction(addWorker);
        workersMenu->addAction(scroolWorker);

        clientsMenu = menuBar()->addMenu(tr("&Klienci"));
        clientsMenu->addAction(client_scroll);
    }

    booksMenu = menuBar()->addMenu(tr("&Książki"));
    booksMenu->addAction(book_add);
    booksMenu->addAction(book_scroll);

    authorsMenu = menuBar()->addMenu(tr("&Autorzy"));
    authorsMenu->addAction(author_add);
    authorsMenu->addAction(author_scroll);

    publisherMenu = menuBar()->addMenu(tr("&Wydawcy"));
    publisherMenu->addAction(publisher_add);
    publisherMenu->addAction(publisher_scroll);

    rentsMenu = menuBar()->addMenu(tr("&Wypożyczenia"));
    rentsMenu->addAction(rent_add);
    rentsMenu->addAction(rent_scroll);

    accountMenu = menuBar()->addMenu(tr("&Twoje konto"));
    accountMenu->addAction(action_menu_account_change_passwd);
    accountMenu->addAction(action_menu_account_logout);
}

void WorkerWindow::create_actions()
{
    // MAIN MENU

    addWorker = new QAction(tr("&Dodaj pracownika"), this);
    connect(addWorker, &QAction::triggered, this, &WorkerWindow::addWorkerSlot);

    scroolWorker = new QAction(tr("&Przeglądaj pracowników"), this);
    connect(scroolWorker, &QAction::triggered, this, &WorkerWindow::scrollWorkerSlot);

    client_scroll = new QAction(tr("&Przeglądaj klientów"), this);
    connect(client_scroll, &QAction::triggered, this, &WorkerWindow::client_scrollSlot);

    book_add = new QAction(tr("&Dodaj książkę"), this);
    connect(book_add, &QAction::triggered, this, &WorkerWindow::book_addSlot);

    book_scroll = new QAction(tr("&Przeglądaj książki"), this);
    connect(book_scroll, &QAction::triggered, this, &WorkerWindow::book_scrollSlot);

    author_add = new QAction(tr("&Dodaj autora"), this);
    connect(author_add, &QAction::triggered, this, &WorkerWindow::author_addSlot);

    author_scroll = new QAction(tr("&Przeglądaj autorów"), this);
    connect(author_scroll, &QAction::triggered, this, &WorkerWindow::author_scrollSlot);

    publisher_add = new QAction(tr("&Dodaj wydawcę"), this);
    connect(publisher_add, &QAction::triggered, this, &WorkerWindow::publisher_addSlot);

    publisher_scroll = new QAction(tr("&Przeglądaj wydawców"), this);
    connect(publisher_scroll, &QAction::triggered, this, &WorkerWindow::publisher_scrollSlot);

    rent_add = new QAction(tr("&Dodaj wypożyczenie"), this);
    connect(rent_add, &QAction::triggered, this, &WorkerWindow::rent_addSlot);

    rent_scroll = new QAction(tr("&Przeglądaj wypożyczenia"), this);
    connect(rent_scroll, &QAction::triggered, this, &WorkerWindow::rent_scrollSlot);

    action_menu_account_change_passwd = new QAction(tr("&Zmień swoje hasło"));
    connect(action_menu_account_change_passwd, &QAction::triggered, this, &WorkerWindow::account_changepasswdSlot);

    action_menu_account_logout = new QAction(tr("&Wyloguj się"));
    connect(action_menu_account_logout, &QAction::triggered, this, &WorkerWindow::account_logoutSlot);

    // TABLE POP UP MENU

    action_table_menu_delete = new QAction(tr("&Usuń rekord"), this);
    connect(action_table_menu_delete, &QAction::triggered, this, &WorkerWindow::delete_slot);

    action_table_menu_save = new QAction(tr("&Zapisz zmiany"), this);
    connect(action_table_menu_save, &QAction::triggered, this, &WorkerWindow::save_slot);
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

    if(stage == "scrollworker") {
        stage_scrollworker();
    }

    if(stage == "changepasswd") {
        stage_changepasswd();
    }
}

QHBoxLayout* WorkerWindow::getSearchBox()
{
    search_input = new QLineEdit;
    search_input->setPlaceholderText("Wpisz tekst który chcesz wyszukać");
    QPushButton* search_button = new QPushButton(tr("&Wyszukaj"));
    connect(search_button, SIGNAL(released()), this, SLOT(search_slot()));

    QHBoxLayout* search_box = new QHBoxLayout;
    search_box->addWidget(search_input);
    search_box->addWidget(search_button);

    return search_box;
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
    setStage("scrollworker");
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
                    setStage("scrollworker");
                }
            }
        }
    }
}

void WorkerWindow::client_scrollSlot()
{
    qDebug() << "client_scrollSlot()";
}

void WorkerWindow::book_addSlot()
{
    qDebug() << "book_addSlot";
}

void WorkerWindow::book_scrollSlot()
{
    qDebug() << "book_scrollSlot";
}

void WorkerWindow::author_addSlot()
{
    qDebug() << "author_addSlot";
}

void WorkerWindow::author_scrollSlot()
{
    qDebug() << "author_scrollSlot";
}

void WorkerWindow::publisher_addSlot()
{
    qDebug() << "publisher_addSlot";
}

void WorkerWindow::publisher_scrollSlot()
{
    qDebug() << "publisher_scrollSlot";
}

void WorkerWindow::rent_addSlot()
{
    qDebug() << "rent_addSlot";
}

void WorkerWindow::rent_scrollSlot()
{
    qDebug() << "rent_scrollSlot";
}

void WorkerWindow::account_changepasswdSlot()
{
    setStage("changepasswd");
}

void WorkerWindow::account_logoutSlot()
{
    this->close();
}

void WorkerWindow::customMenuRequested(QPoint pos)
{
    QModelIndex index = table->indexAt(pos);
    //index = index.siblingAtColumn(0);
    //table_row_id = index.data().toInt();
    table_row_id = index.row();

    QMenu* tab_menu = new QMenu(this);
    tab_menu->addAction(action_table_menu_delete);
    tab_menu->addAction(action_table_menu_save);
    tab_menu->popup(table->viewport()->mapToGlobal(pos));
}

void WorkerWindow::search_slot()
{
    QSortFilterProxyModel proxy;
    proxy.setSourceModel(table->model());
    proxy.setFilterFixedString(search_input->text());

    bool flag = false;

    for(int i=0; i<table->model()->columnCount(); i++) {
        proxy.setFilterKeyColumn(i);
        QModelIndex index = proxy.mapToSource(proxy.index(0, 0));
        if(index.isValid()) {
            table->scrollTo(index, QAbstractItemView::EnsureVisible);
            table->selectRow(index.row());
            flag = true;
            break;
        }
    }

    if(!flag) {
        QMessageBox hint;
        hint.warning(nullptr, "Brak wyników", "Brak wyników wyszukiwania dla podanej frazy");
    }
}

void WorkerWindow::delete_slot()
{
    QSqlTableModel* t_model = (QSqlTableModel*)(table->model());
    QSqlRecord t_record = t_model->record(table_row_id);

    if(t_model->tableName() == "worker") {
        if(t_record.value(0).toInt() == 1 || t_record.value(0).toUInt() == worker->getID()) {
            QMessageBox hint;
            hint.warning(nullptr, "Blokada dostępu" , "Nie można usunąć konta root lub swojego wlasnego konta");
            return;
        }
    }

    t_model->removeRow(table_row_id);
    t_model->submitAll();
}

void WorkerWindow::save_slot()
{
    QSqlTableModel* t_model = (QSqlTableModel*)(table->model());
    QSqlRecord t_record = t_model->record(table_row_id);
    QString error_text;
    bool ok = true;

    if(t_model->tableName() == "worker") {
        if(t_record.value(0).toInt() == 1) {
            ok = false;
            error_text = "Nie można modyfikować konta root";
        }
        User user(t_record.value(2).toString(), t_record.value(3).toString());
        ok = ok && user.validate();
        Worker worker(t_record.value(1).toInt(), t_record.value(4).toString(), t_record.value(5).toString());
        ok = ok && worker.validate();
    }

    if(!ok) {
        if(!error_text.isEmpty()) {
            QMessageBox hint;
            hint.warning(nullptr, "Blokada dostępu" , error_text);
        }
        return;
    }

    t_model->submitAll();
}

void WorkerWindow::table_on_change()
{
    QSqlTableModel* t_model = (QSqlTableModel*)(table->model());
    t_model->revertAll();
}

void WorkerWindow::account_changepasswd()
{
    QString old_password = register_worker_password->text();
    QString new_password = register_worker_password_repeat->text();
    if(worker->compare_passwords(User::password_hash(old_password), true)) {
        if(worker->change_password(new_password, ACCOUNT_WORKER)) {
            QMessageBox hint;
            hint.information(nullptr, "Zmiana hasła", "Pomyślna zmiana hasła");
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

void WorkerWindow::stage_scrollworker()
{
    table = new QTableView;

    QSqlTableModel* t_model = new QSqlTableModel;
    t_model->setTable("worker");
    t_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    t_model->select();
    t_model->setHeaderData(1, Qt::Horizontal, tr("Typ użytkownika"));
    t_model->setHeaderData(2, Qt::Horizontal, tr("Login"));
    t_model->setHeaderData(4, Qt::Horizontal, tr("Imię"));
    t_model->setHeaderData(5, Qt::Horizontal, tr("Nazwisko"));

    table->setModel(t_model);
    table->hideColumn(0);
    table->hideColumn(3);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(table, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));
    connect(table->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(table_on_change()));
    table->setSortingEnabled(true);
    table->show();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(getSearchBox());
    layout->addWidget(table);

    qDeleteAll(widget->children());
    widget->setLayout(layout);
}

void WorkerWindow::stage_changepasswd()
{
    register_worker_password = new QLineEdit;
    register_worker_password->setEchoMode(QLineEdit::Password);
    register_worker_password->setPlaceholderText("Stare hasło");

    register_worker_password_repeat = new QLineEdit;
    register_worker_password_repeat->setEchoMode(QLineEdit::Password);
    register_worker_password_repeat->setPlaceholderText("Nowe hasło");

    QFormLayout* form = new QFormLayout;
    form->addRow(tr("&Stare hasło"), register_worker_password);
    form->addRow(tr("&Nowe hasło"), register_worker_password_repeat);

    QPushButton* change_passwd_button = new QPushButton(tr("&Zmień swoje hasło"));
    connect(change_passwd_button, SIGNAL(released()), this, SLOT(account_changepasswd()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->addLayout(form);
    layout->addWidget(change_passwd_button);

    qDeleteAll(widget->children());
    widget->setLayout(layout);
}
