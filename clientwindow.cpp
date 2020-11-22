#include "clientwindow.h"

ClientWindow::ClientWindow()
{
    this->setWindow();

}

void ClientWindow::setWindow()
{
    setMinimumSize(500, 400);
    resize(800, 600);
    setWindowTitle("Witaj kliencie");
}
