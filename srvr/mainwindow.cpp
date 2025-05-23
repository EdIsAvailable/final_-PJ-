/*
#include "mainwindow.h"
#include "startscreen.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::createClient()
{
    StartScreen s;
    s.exec();
    return nullptr;
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void MainWindow::on_sendMessageButton_clicked()
{

}


void MainWindow::on_privateMessageSendButton_clicked()
{

}


void MainWindow::on_actionOpen_another_client_triggered()
{
    createClient();
}


void MainWindow::on_actionCloseClient_triggered()
{

}

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
#include "Chat.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Инициализация чата
    _chat = new Chat();

    // Установка заголовка окна
    setWindowTitle("Мессенджер");

    // Скрываем интерфейс до авторизации
    ui->centralwidget->setEnabled(false);

    // Инициализация репозитория пользователей
    _userRepo = new UserRepository();

    // Автоматически открываем стартовый экран при запуске
    QTimer::singleShot(100, this, &MainWindow::showStartScreen);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _chat;
    delete _userRepo;
    if (_currentUser) {
        delete _currentUser;
    }
}

void MainWindow::showStartScreen()
{
    StartScreen startScreen;
    int result = startScreen.exec();

    if (result == QDialog::Accepted) {
        // Пользователь авторизовался
        _currentUser = startScreen.getLoggedUser();

        if (_currentUser) {
            // Включаем интерфейс
            ui->centralwidget->setEnabled(true);

            // Устанавливаем заголовок окна с именем пользователя
            setWindowTitle("Мессенджер - " + QString::fromStdString(_currentUser->getName()));

            // Обновляем список пользователей
            updateUsersList();

            // Загружаем сообщения для текущего пользователя
            loadMessages();
        } else {
            // Если пользователь не авторизован, закрываем приложение
            QMessageBox::critical(this, "Ошибка", "Не удалось авторизоваться");
            close();
        }
    } else {
        // Пользователь отменил авторизацию, закрываем приложение
        close();
    }
}

void MainWindow::updateUsersList()
{
    ui->userListWidget->clear();

    // Добавляем запись "Всем" для общего чата
    QListWidgetItem *allItem = new QListWidgetItem("Всем (ALL)");
    allItem->setData(Qt::UserRole, "ALL");
    ui->userListWidget->addItem(allItem);

    // Здесь нужно загрузить список пользователей из БД
    // и добавить их в userListWidget
    // Это упрощенная версия, вам потребуется доработать ее

    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT Username FROM Users WHERE Username != 'ALL'"
            ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            std::string username = res->getString("Username");
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(username));
            item->setData(Qt::UserRole, QString::fromStdString(username));
            ui->userListWidget->addItem(item);
        }
    }
    catch (sql::SQLException& e) {
        QMessageBox::critical(this, "Ошибка базы данных",
                              QString("Ошибка SQL: %1 (код: %2)").arg(e.what()).arg(e.getErrorCode()));
    }
}

void MainWindow::loadMessages()
{
    ui->chatTextEdit->clear();

    // Загружаем личные сообщения
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT u.Username AS Sender, m.MessageText, m.Timestamp FROM Messages m "
            "JOIN Users u ON m.SenderID = u.UserID "
            "WHERE ReceiverID = (SELECT UserID FROM Users WHERE Username = ?) "
            "ORDER BY m.Timestamp ASC"
            ));
        pstmt->setString(1, _currentUser->getLogin());
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            std::string sender = res->getString("Sender");
            std::string message = res->getString("MessageText");
            std::string timestamp = res->getString("Timestamp");

            QString formattedMessage = QString("[%1] %2: %3")
                                           .arg(QString::fromStdString(timestamp))
                                           .arg(QString::fromStdString(sender))
                                           .arg(QString::fromStdString(message));

            ui->chatTextEdit->append(formattedMessage);
        }
    }
    catch (sql::SQLException& e) {
        QMessageBox::critical(this, "Ошибка базы данных",
                              QString("Ошибка SQL: %1 (код: %2)").arg(e.what()).arg(e.getErrorCode()));
    }

    // Загружаем сообщения для всех пользователей
    try {
        auto con = connectToDatabase();
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT u.Username AS Sender, m.MessageText, m.Timestamp FROM Messages m "
            "JOIN Users u ON m.SenderID = u.UserID "
            "WHERE ReceiverID = (SELECT UserID FROM Users WHERE Username = 'ALL') "
            "ORDER BY m.Timestamp ASC"
            ));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            std::string sender = res->getString("Sender");
            std::string message = res->getString("MessageText");
            std::string timestamp = res->getString("Timestamp");

            QString formattedMessage = QString("[%1] [Всем] %2: %3")
                                           .arg(QString::fromStdString(timestamp))
                                           .arg(QString::fromStdString(sender))
                                           .arg(QString::fromStdString(message));

            ui->chatTextEdit->append(formattedMessage);
        }
    }
    catch (sql::SQLException& e) {
        QMessageBox::critical(this, "Ошибка базы данных",
                              QString("Ошибка SQL: %1 (код: %2)").arg(e.what()).arg(e.getErrorCode()));
    }
}

MainWindow *MainWindow::createClient()
{
    MainWindow *newWindow = new MainWindow();
    newWindow->show();
    return newWindow;
}

void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}

void MainWindow::on_sendMessageButton_clicked()
{
    QString message = ui->messageLineEdit->text().trimmed();

    if (message.isEmpty()) {
        return;
    }

    try {
        // Отправляем сообщение всем пользователям
        _chat->AddMessage(_currentUser->getLogin(), "ALL", message.toStdString());

        // Очищаем поле ввода
        ui->messageLineEdit->clear();

        // Обновляем отображение сообщений
        loadMessages();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при отправке сообщения: %1").arg(e.what()));
    }
}

void MainWindow::on_privateMessageSendButton_clicked()
{
    // Получаем выбранного пользователя
    QListWidgetItem *selectedItem = ui->userListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "Предупреждение", "Выберите получателя сообщения");
        return;
    }

    QString recipient = selectedItem->data(Qt::UserRole).toString();
    QString message = ui->privateMessageLineEdit->text().trimmed();

    if (message.isEmpty()) {
        return;
    }

    try {
        // Отправляем частное сообщение
        _chat->AddMessage(_currentUser->getLogin(), recipient.toStdString(), message.toStdString());

        // Очищаем поле ввода
        ui->privateMessageLineEdit->clear();

        // Обновляем отображение сообщений
        loadMessages();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка при отправке частного сообщения: %1").arg(e.what()));
    }
}

void MainWindow::on_actionOpen_another_client_triggered()
{
    createClient();
}

void MainWindow::on_actionCloseClient_triggered()
{
    close();
}

void MainWindow::on_refreshButton_clicked()
{
    loadMessages();
    updateUsersList();
}
