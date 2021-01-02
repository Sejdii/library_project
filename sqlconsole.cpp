#include "sqlconsole.h"

SqlConsole::SqlConsole(QWidget *parent) : QMainWindow(parent)
{
    this->set_window();
    widget = new QWidget;
    setCentralWidget(widget);
    
    stage_main();
}

void SqlConsole::set_window()
{
    setMinimumSize(400, 300);
    resize(700, 500);
    setWindowTitle("Konsola SQL");
}

void SqlConsole::onsubmit()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query_text->text());
    model->submit();
    
    table->setModel(model);
}

// #################################
// #            STAGES             #
// #################################

void SqlConsole::stage_main()
{
    query_text = new QLineEdit;
    query_text->setPlaceholderText("Wpisz tutaj polecenie SQL");
    
    QPushButton* button = new QPushButton(tr("Wykonaj"));
    connect(button, SIGNAL(released()), this, SLOT(onsubmit()));
    
    table = new QTableView;
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(query_text);
    layout->addWidget(button);
    layout->addWidget(table);
    
    widget->setLayout(layout);
}
