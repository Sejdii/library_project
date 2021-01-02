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

// #################################
// #            SLOTS              #
// #################################

void ClientWindow::search_slot()
{
    QString like = search_input->text();
    
    stage_main_stage(like);
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
