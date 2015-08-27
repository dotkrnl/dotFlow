#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont(
                ":/fonts/res/fontawesome.ttf");
    QFontDatabase::addApplicationFont(
                ":/fonts/res/menlo.ttc");

    MainWindow w;
    w.show();

    return a.exec();
}
