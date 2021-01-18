/**
  * @file color.h
  * @brief Plik z klasą Color
  */

#ifndef COLOR_H
#define COLOR_H

#include <QString>

/**
 * @brief Klasa Color dostarcza metody odpowiadające za wygląd elementów w aplikacji
 */
class Color
{
public:
    /**
     * @brief Konstruktor
     */
    Color();
    
    /**
     * @brief Zwraca stylesheet dla  przycisku
     * @return stylesheet
     */
    static QString get_button_style();
    /**
     * @brief Zwraca stylesheet dla widgetu
     * @return stylesheet
     */
    static QString get_widget_style();
    /**
     * @brief Zwraca stylesheet dla okna
     * @return stylesheet
     */
    static QString get_window_style();
    /**
     * @brief Zwraca stylesheet dla nagłówka tabeli
     * @return stylesheet
     */
    static QString get_table_header_style();
};

#endif // COLOR_H
