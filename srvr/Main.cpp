
#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем информацию о приложении
    QApplication::setApplicationName("Chat");
    QApplication::setApplicationVersion("1.0");

    // Безопасно обрабатываем аргумент командной строки (для тестов)
    if (argc > 1) {
        QString str = QString::fromUtf8(argv[1]);
    //QByteArray ba = str.toUtf8();
        qDebug() << "Аргумент:" << str;
    }

    // Создаем и показываем главное окно
    MainWindow w;
    w.show();

    return a.exec();
}
