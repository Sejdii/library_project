#include "lib/color.h"

Color::Color()
{
    
}

QString Color::get_button_style()
{
    return "background-color: #6200EE; color: white; font-size: 16px;";
}

QString Color::get_widget_style()
{
    return "background-color: white; font-size: 12px;";
}

QString Color::get_window_style()
{
    return "font-family: Lato;";
}

QString Color::get_table_header_style()
{
    return "QHeaderView::section {background-color: #03DAC6; color: black}";
}
