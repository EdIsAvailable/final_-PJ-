/*
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* createClient();

private slots:
    void on_messageLineEdit_returnPressed();
    void on_sendMessageButton_clicked();
    void on_privateMessageSendButton_clicked();
    void on_actionOpen_another_client_triggered();
    void on_actionCloseClient_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "UserRepository.h"
#include "Chat.h"
#include "Acc.h"
#include "db.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* createClient();

private slots:
    void on_messageLineEdit_returnPressed();
    void on_sendMessageButton_clicked();
    void on_privateMessageSendButton_clicked();
    void on_actionOpen_another_client_triggered();
    void on_actionCloseClient_triggered();
    void showStartScreen();
    void on_refreshButton_clicked();

private:
    Ui::MainWindow *ui;
    Chat *_chat;
    UserRepository *_userRepo;
    Acc *_currentUser = nullptr;

    void updateUsersList();
    void loadMessages();
};

#endif // MAINWINDOW_H

