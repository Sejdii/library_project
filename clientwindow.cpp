#include "clientwindow.h"

ClientWindow::ClientWindow(unsigned int id)
{
    this->setWindow();
    client = new Client(id);
    
    widget = new QWidget;
    setCentralWidget(widget);
    
    stage_main_stage();
}

void ClientWindow::setWindow()
{
    setMinimumSize(600, 500);
    resize(800, 600);
    setWindowTitle("Witaj kliencie");
    
    this->create_menu();
}

QHBoxLayout* ClientWindow::getSearchBox(QString value)
{
    search_input = new QLineEdit;
    search_input->setText(value);
    search_input->setPlaceholderText("Wpisz tekst który chcesz wyszukać");
    QPushButton* search_button = new QPushButton(tr("&Wyszukaj"));
    connect(search_button, SIGNAL(released()), this, SLOT(search_slot()));

    QHBoxLayout* search_box = new QHBoxLayout;
    search_box->addWidget(search_input);
    search_box->addWidget(search_button);

    return search_box;
}

QTableView* ClientWindow::get_search_result(QString like)
{
    QSqlQuery query;
    QTableView* layout = new QTableView;
    
    if(like.length() > 0) {
        like = "%" + like + "%";
        
        if(!query.prepare("SELECT b.isbn, b.title, p.name, b.publish_year, a.name || ' ' || a.surname as author FROM book as b INNER JOIN publisher as p ON  p.id=b.publisher_id INNER JOIN author as a ON a.id=b.author_id WHERE b.isbn || b.title || p.name || b.publish_year || a.name || a.surname LIKE ?")) {
            qDebug() << "standard search result prepere error" << query.lastError();
            return NULL;
        }
        
        query.addBindValue(like);
    } else {
        if(!query.prepare("SELECT b.isbn, b.title, p.name, b.publish_year, a.name || ' ' || a.surname as author FROM book as b INNER JOIN publisher as p ON  p.id=b.publisher_id INNER JOIN author as a ON a.id=b.author_id")) {
            qDebug() << "standard search result prepere error" << query.lastError();
            return NULL;
        }
    }
    
    if(!query.exec()) {
        qDebug() << "standard search result exec error" << query.lastError();
        return NULL;
    }
    
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, "ISBN");
    model->setHeaderData(1, Qt::Horizontal, "Tytuł");
    model->setHeaderData(2, Qt::Horizontal, "Wydawca");
    model->setHeaderData(3, Qt::Horizontal, "Rok wydania");
    model->setHeaderData(4, Qt::Horizontal, "Autor");
    
    layout->setModel(model);
    
    return layout;
}

void ClientWindow::create_menu()
{
    /*
     * MENU HIERARCHY
     * 
     * Narzędzia
     *  --> Szukaj książki
     *  --> Sprawdź dostępność książki
     * 
     * Wypożyczenia
     *  --> Moje aktywne wypożyczenia
     *  --> Historia wypożyczeń
     * 
     * Konto
     *  --> Zmień hasło
     *  --> Wyloguj się
    */
    
    // Actions
    
    action_menu_main = new QAction(tr("Szukaj książki"), this);
    connect(action_menu_main, &QAction::triggered, this, &ClientWindow::slot_menu_main);
    action_menu_check_availability = new QAction(tr("Sprawdź dostępność książki"), this);
    connect(action_menu_check_availability, &QAction::triggered, this, &ClientWindow::slot_menu_check_availability);
    
    action_menu_change_password = new QAction(tr("Zmień hasło"), this);
    connect(action_menu_change_password, &QAction::triggered, this, &ClientWindow::slot_menu_change_password);
    action_menu_logout = new QAction(tr("Wyloguj się"), this);
    connect(action_menu_logout, &QAction::triggered, this, &ClientWindow::slot_menu_logout);
    
    action_menu_not_ended_rents = new QAction(tr("Moje aktywne wypożyczenia"), this);
    connect(action_menu_not_ended_rents, &QAction::triggered, this, &ClientWindow::slot_menu_not_ended_rents);
    action_menu_all_rents = new QAction(tr("Historia wypożyczeń"), this);
    connect(action_menu_all_rents, &QAction::triggered, this, &ClientWindow::slot_menu_all_rents);
    
    // Menus
    
    menu_tools = menuBar()->addMenu(tr("Narzędzia"));
    menu_tools->addAction(action_menu_main);
    menu_tools->addAction(action_menu_check_availability);

    menu_rents = menuBar()->addMenu(tr("Wypożyczenia"));
    menu_rents->addAction(action_menu_not_ended_rents);
    menu_rents->addAction(action_menu_all_rents);
    
    menu_account = menuBar()->addMenu(tr("Konto"));
    menu_account->addAction(action_menu_change_password);
    menu_account->addAction(action_menu_logout);
}

// #################################
// #            SLOTS              #
// #################################

void ClientWindow::search_slot()
{
    QString like = search_input->text();
    
    stage_main_stage(like);
}

void ClientWindow::slot_menu_check_availability()
{
    stage_check_availability();
}

void ClientWindow::slot_menu_change_password()
{
    qDebug() << "menu change passwd";
}

void ClientWindow::slot_menu_logout()
{
    close();
}

void ClientWindow::slot_menu_main()
{
    stage_main_stage();
}

void ClientWindow::slot_menu_not_ended_rents()
{
    stage_not_ended_rents();
}

void ClientWindow::slot_menu_all_rents()
{
    stage_all_rents();
}

void ClientWindow::check_availability_slot()
{
    QString book_isbn = check_isbn->text();
    int book_id = Book::is_exist(book_isbn);
    QString info = "";
    if(book_id >= 0) {
        if(Book::check_availability(book_id)) {
            info = "Książka jest dostępna";
        } else {
            info = "Książka nie jest dostępna";
        }
    } else {
        info = "Książka o podanym ISBN nie istnieje";
    }
    
    QMessageBox hint;
    hint.warning(nullptr, "Informacja o dostępności książki", info);
}

// #################################
// #            STAGES             #
// #################################

void ClientWindow::stage_main_stage(QString like)
{
    search_result = get_search_result(like);
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(this->getSearchBox(like));
    layout->addWidget(search_result);
    
    qDeleteAll(widget->children());
    widget->setLayout(layout);
}

void ClientWindow::stage_check_availability()
{
    QLabel* label = new QLabel("Wprowadź ISBN książki");
    
    check_isbn = new QLineEdit;
    check_isbn->setPlaceholderText("Wprowadź ISBN");
    
    QPushButton* button = new QPushButton("Sprawdź");
    connect(button, SIGNAL(released()), this, SLOT(check_availability_slot()));
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(check_isbn);
    layout->addWidget(button);
    
    layout->setAlignment(Qt::AlignTop);
    
    qDeleteAll(widget->children());
    widget->setLayout(layout);
}

void ClientWindow::stage_not_ended_rents()
{
    QLabel* label = new QLabel(tr("<h1>Twoje aktywne wypożyczenia</h1>"));
    
    QTableView* table = new QTableView;
    
    QSqlQuery query;
    if(!query.prepare("SELECT b.title,  r.start_date, r.end_date  FROM rent as r INNER JOIN book as  b ON r.book_id=b.id WHERE client_id=? AND ended IS NULL")) {
        qDebug() << "not eneded rents prepere error" << query.lastError();
    }
    
    query.addBindValue(client->getID());
    
    if(!query.exec()) {
        qDebug() << "not eneded rent exec error" << query.lastError();
    }
    
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Tytuł"));
    model->setHeaderData(1, Qt::Horizontal, tr("Początek wypożyczenia"));
    model->setHeaderData(2, Qt::Horizontal, tr("Termin końca wypożyczenia"));
    
    table->setModel(model);
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(table);
    
    layout->setAlignment(Qt::AlignTop);
    
    qDeleteAll(widget->children());
    widget->setLayout(layout);
}

void ClientWindow::stage_all_rents()
{
    QLabel* label = new QLabel(tr("<h1>Historia twoich zakończonych wypożyczeń</h1>"));
    
    QTableView* table = new QTableView;
    
    QSqlQuery query;
    if(!query.prepare("SELECT b.title,  r.start_date, r.end_date, r.ended  FROM rent as r INNER JOIN book as  b ON r.book_id=b.id WHERE client_id=? AND ended IS NOT NULL")) {
        qDebug() << "all rents prepere error" << query.lastError();
    }
    
    query.addBindValue(client->getID());
    
    if(!query.exec()) {
        qDebug() << "all rents exec error" << query.lastError();
    }
    
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("Tytuł"));
    model->setHeaderData(1, Qt::Horizontal, tr("Początek wypożyczenia"));
    model->setHeaderData(2, Qt::Horizontal, tr("Termin końca wypożyczenia"));
    model->setHeaderData(3, Qt::Horizontal, tr("Termin oddania"));
    
    table->setModel(model);
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(table);
    
    layout->setAlignment(Qt::AlignTop);
    
    qDeleteAll(widget->children());
    widget->setLayout(layout);
}
