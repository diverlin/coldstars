#include "mainwindow.hpp"

#include <QtWidgets/QApplication>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
//    window.adjustSize();

    return app.exec();
}
