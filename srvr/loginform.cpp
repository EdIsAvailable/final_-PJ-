/*
#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}


void LoginForm::on_buttonBox_accepted()
{

}


void LoginForm::on_buttonBox_rejected()
{

}


void LoginForm::on_registrationPushButton_clicked()
{

}
*/


#include "loginform.h"
#include "ui_loginform.h"
#include "UserRepository.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

LoginForm::LoginForm(QWidget *parent)
    : QDialog(parent)//QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    setWindowTitle("Вход в систему");

    // Создаем элементы формы
    QLabel *loginLabel = new QLabel("Логин:", this);
    QLabel *passwordLabel = new QLabel("Пароль:", this);

    loginEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);

    QPushButton *loginButton = new QPushButton("Войти", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);

    // Создаем layout для формы
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создаем горизонтальный layout для метки и поля логина
    QHBoxLayout *loginLayout = new QHBoxLayout();
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);

    // Создаем горизонтальный layout для метки и поля пароля
    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    // Создаем горизонтальный layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(cancelButton);

    // Добавляем все layouts в главный layout
    mainLayout->addLayout(loginLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(buttonLayout);

    // Устанавливаем layout для формы
    setLayout(mainLayout);

    // Подключаем сигналы
    connect(loginButton, &QPushButton::clicked, this, &LoginForm::on_buttonBox_accepted);
    connect(cancelButton, &QPushButton::clicked, this, &LoginForm::on_buttonBox_rejected);

    // Создаем репозиторий пользователей
    _userRepo = new UserRepository();
}

LoginForm::~LoginForm()
{
    delete ui;
    delete _userRepo;
}

void LoginForm::on_buttonBox_accepted()
{
    QString login = loginEdit->text();
    QString password = passwordEdit->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите логин и пароль");
        return;
    }

    // Пытаемся авторизовать пользователя
    std::string loginStr = login.toStdString();
    std::string passwordStr = password.toStdString();

    _user = _userRepo->AuthorizeUser(loginStr, passwordStr);

    if (_user) {
        // Успешная авторизация
        QMessageBox::information(this, "Успех", "Вход выполнен успешно!");
        _loginSuccessful = true;
        close();
    } else {
        // Ошибка авторизации
        QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
    }
}

void LoginForm::on_buttonBox_rejected()
{
    close();
}

void LoginForm::on_registrationPushButton_clicked()
{
    // Эта функция не используется в новом GUI
}

bool LoginForm::isLoginSuccessful() const
{
    return _loginSuccessful;
}

Acc* LoginForm::getUser() const
{
    return _user;
}

/*
#include "loginform.h"
#include "ui_loginform.h"
#include "UserRepository.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

LoginForm::LoginForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginForm)
    , _userRepo(nullptr)          // Инициализируем репозиторий
    , _user(nullptr)              // Инициализируем указатель на пользователя
    , _loginSuccessful(false)     // Инициализируем флаг успешного входа
{
    ui->setupUi(this);
    setWindowTitle("Вход в систему");

    // Получаем указатели на элементы из UI файла
    loginEdit = ui->loginEdit;
    passwordEdit = ui->passwordEdit_2; // Внимание: в UI файле поле называется passwordEdit_2

    // Подключаем сигналы кнопок из UI файла
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &LoginForm::on_buttonBox_accepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &LoginForm::on_buttonBox_rejected);
    connect(ui->registrationPushButton, &QPushButton::clicked, this, &LoginForm::on_registrationPushButton_clicked);

    // Создаем репозиторий пользователей
    _userRepo = new UserRepository();
}

LoginForm::~LoginForm()
{
    delete ui;
    if (_userRepo) {
        delete _userRepo; // Освобождаем память репозитория
    }
}

void LoginForm::on_buttonBox_accepted()
{
    // Получаем введенные данные
    QString login = loginEdit->text().trimmed();
    QString password = passwordEdit->text().trimmed();

    // Проверяем, что поля не пустые
    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите логин и пароль");
        return;
    }

    try {
        // Пытаемся авторизовать пользователя
        std::string loginStr = login.toStdString();
        std::string passwordStr = password.toStdString();

        _user = _userRepo->AuthorizeUser(loginStr, passwordStr);

        if (_user) {
            // Успешная авторизация
            QMessageBox::information(this, "Успех", "Вход выполнен успешно!");
            _loginSuccessful = true;
            //close(); // Закрываем окно входа
            accept();
        } else {
            // Ошибка авторизации
            QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
        }
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString("Ошибка авторизации: %1").arg(e.what()));
    }
    catch (...) {
        QMessageBox::critical(this, "Ошибка", "Неизвестная ошибка при авторизации");
    }
}

void LoginForm::on_buttonBox_rejected()
{
    // Закрываем форму без входа
    //close();
    reject();
}

void LoginForm::on_registrationPushButton_clicked()
{

    close();
}

// Возвращает статус успешного входа
bool LoginForm::isLoginSuccessful() const
{
    return _loginSuccessful;
}

// Возвращает указатель на авторизованного пользователя
Acc* LoginForm::getUser() const
{
    return _user;
}
*/
