#include "sqlconsole.h"

SqlConsole::SqlConsole(QWidget *parent) : QMainWindow(parent)
{
    this->set_window();
    widget = new QWidget;
    setCentralWidget(widget);
    widget->setStyleSheet(Color::get_widget_style());
    
    stage_main();
}

void SqlConsole::set_window()
{
    setMinimumSize(400, 300);
    resize(700, 500);
    setWindowTitle("Konsola SQL");
    
    this->setStyleSheet(Color::get_window_style());
}

void SqlConsole::onsubmit()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query_text->text());
    table->setModel(model);
    
    if (model->lastError().type() != QSqlError::NoError) {
        QMessageBox hint;
        hint.warning(nullptr, "Wystąpił błąd zapytania", model->lastError().text());
    }
}

// #################################
// #            STAGES             #
// #################################

void SqlConsole::stage_main()
{
    query_text = new QLineEdit;
    query_text->setPlaceholderText("Wpisz tutaj polecenie SQL");
    
    QPushButton* button = new QPushButton(tr("Wykonaj"));
    button->setStyleSheet(Color::get_button_style());
    connect(button, SIGNAL(released()), this, SLOT(onsubmit()));
    
    table = new QTableView;
    table->setStyleSheet(Color::get_table_header_style());
    
    QLabel* label = new QLabel("<i>Konsola służy do wyświetlania poleceń SELECT w postaci tabeli </i>");
    
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(query_text);
    layout->addWidget(button);
    layout->addWidget(label);
    layout->addWidget(table);
    
    widget->setLayout(layout);
}
