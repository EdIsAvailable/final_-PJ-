#include <QString>
#include <QApplication>
#include <QDebug>
#include <iostream>
#include <QTranslator>
#include "CommandLineInterface.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = MainWindow::createClient();
    if(w)
    w->show();
    else
        return 0;

    QTranslator myappTranslator;
    myappTranslator.load("translations/my_ru.qm");
    a.installTranslator(&myappTranslator);

    QTranslator defaultTranslator;
    defaultTranslator.load("translations/qt_ru.qm");
    a.installTranslator(&defaultTranslator);

    //MainWindow::createClient();

    return a.exec();
}
