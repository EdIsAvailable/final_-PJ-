/*
#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);
}

StartScreen::~StartScreen()
{
    delete ui;
}
*/

#include "startscreen.h"
#include "loginform.h"
#include "registrationform.h"
#include "ui_startscreen.h"
#include <QVBoxLayout>
#include <QPushButton>

StartScreen::StartScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    // Установка заголовка окна
    setWindowTitle("Мессенджер - Начальный экран");

    // Создаем кнопки для входа и регистрации
    QPushButton *loginButton = new QPushButton("Войти", this);
    QPushButton *registerButton = new QPushButton("Зарегистрироваться", this);
    QPushButton *exitButton = new QPushButton("Выход", this);

    // Создаем вертикальный layout и добавляем кнопки
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);
    layout->addWidget(exitButton);

    // Устанавливаем layout для диалога
    setLayout(layout);

    // Подключаем сигналы кнопок
    connect(loginButton, &QPushButton::clicked, this, &StartScreen::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &StartScreen::onRegisterClicked);
    connect(exitButton, &QPushButton::clicked, this, &StartScreen::reject);
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::onLoginClicked()
{
    // Открываем форму входа
    LoginForm *loginForm = new LoginForm(this);
    loginForm->exec();

    // Если успешно авторизовались, принимаем диалог
    if (loginForm->isLoginSuccessful()) {
        accept();
    }

    delete loginForm;
}

void StartScreen::onRegisterClicked()
{
    // Открываем форму регистрации
    RegistrationForm *regForm = new RegistrationForm(this);
    regForm->exec();

    // Если пользователь зарегистрировался, можно открыть форму входа
    if (regForm->isRegistrationSuccessful()) {
        onLoginClicked();
    }

    delete regForm;
}

Acc* StartScreen::getLoggedUser() const
{
    return _loggedUser;
}

void StartScreen::setLoggedUser(Acc* user)
{
    _loggedUser = user;
}
