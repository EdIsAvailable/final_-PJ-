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
    : QWidget(parent)
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

