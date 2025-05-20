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

*/
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
