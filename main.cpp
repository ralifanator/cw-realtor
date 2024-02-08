#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("cw-realtor_ru_RU", ".");
    qApp->installTranslator(&translator);
    MainWindow w;
    w.show();

    return a.exec();
}
