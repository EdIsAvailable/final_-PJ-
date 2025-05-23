/*
#include <cstdio>
#include <iostream>
#include <thread>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <QApplication>
#include "mainwindow.h"
#include "Acc.h"
#include "Socket.h"
#include "Chat.h"
#include "Server.h"
#include "db.h"
#include "NewUser.h"
#include "Logger.h"

using namespace std;

Server* _server;

int main(int argc, char *argv[]) {
     SetConsoleOutputCP(CP_UTF8);

  QApplication a(argc, argv);
    MainWindow w;
  w.show();
    _server = new Server();
    _server->MainProcess();
    delete _server; 
   // return 0;
     return a.exec();
}


#include <QApplication>
#include <QTimer>

#include "MainWindow.h"
#include "Server.h"

Server* _server;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    _server = new Server();

    // Запускаем MainProcess() после запуска GUI
    QTimer::singleShot(0, []() {
        _server->MainProcess();
    });

    return a.exec();
}
*/

#include <QApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Устанавливаем информацию о приложении
    QApplication::setApplicationName("Chat Application");
    QApplication::setApplicationVersion("1.0");

    // Безопасно обрабатываем аргумент командной строки (если есть)
    if (argc > 1) {
        QString str = QString::fromUtf8(argv[1]);
        QByteArray ba = str.toUtf8();
        qDebug() << "Аргумент:" << str;
    }

    // Создаем и показываем главное окно
    MainWindow w;
    w.show();

    return a.exec();
}
