/*
#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_loginButton_clicked()
{

}


void RegistrationForm::on_buttonBox_accepted()
{

}


void RegistrationForm::on_buttonBox_rejected()
{

}

*/

#include "registrationform.h"
#include "ui_registrationform.h"
#include "UserRepository.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

RegistrationForm::RegistrationForm(QWidget *parent)
   // : QWidget(parent)
    : QDialog(parent)
    , ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
    setWindowTitle("Регистрация нового пользователя");

    // Создаем элементы формы
    QLabel *nameLabel = new QLabel("Имя:", this);
    QLabel *loginLabel = new QLabel("Логин:", this);
    QLabel *passwordLabel = new QLabel("Пароль:", this);
    QLabel *confirmPasswordLabel = new QLabel("Подтвердите пароль:", this);

    nameEdit = new QLineEdit(this);
    loginEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);

    QPushButton *registerButton = new QPushButton("Зарегистрироваться", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);

    // Создаем layout для формы
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создаем горизонтальные layouts для полей ввода
    QHBoxLayout *nameLayout = new QHBoxLayout();
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameEdit);

    QHBoxLayout *loginLayout = new QHBoxLayout();
    loginLayout->addWidget(loginLabel);
    loginLayout->addWidget(loginEdit);

    QHBoxLayout *passwordLayout = new QHBoxLayout();
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    QHBoxLayout *confirmPasswordLayout = new QHBoxLayout();
    confirmPasswordLayout->addWidget(confirmPasswordLabel);
    confirmPasswordLayout->addWidget(confirmPasswordEdit);

    // Создаем горизонтальный layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(cancelButton);

    // Добавляем все layouts в главный layout
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(loginLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(confirmPasswordLayout);
    mainLayout->addLayout(buttonLayout);

    // Устанавливаем layout для формы
    setLayout(mainLayout);

    // Подключаем сигналы
    connect(registerButton, &QPushButton::clicked, this, &RegistrationForm::on_buttonBox_accepted);
    connect(cancelButton, &QPushButton::clicked, this, &RegistrationForm::on_buttonBox_rejected);

    // Создаем репозиторий пользователей
    _userRepo = new UserRepository();
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
    delete _userRepo;
}

void RegistrationForm::on_loginButton_clicked()
{
    // Эта функция не используется в новом GUI
}

void RegistrationForm::on_buttonBox_accepted()
{
    QString name = nameEdit->text();
    QString login = loginEdit->text();
    QString password = passwordEdit->text();
    QString confirmPassword = confirmPasswordEdit->text();

    // Проверяем, что все поля заполнены
    if (name.isEmpty() || login.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все поля");
        return;
    }

    // Проверяем, что пароли совпадают
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают");
        return;
    }

    try {
        // Попытка регистрации в базе данных
        std::string loginStr = login.toStdString();
        std::string passwordStr = password.toStdString();

        // Проверка, существует ли пользователь
        if (_userRepo->FindUser(loginStr)) {
            QMessageBox::warning(this, "Ошибка", "Пользователь с таким логином уже существует");
            return;
        }

        // Регистрируем пользователя через UserRepository
        _user = new Acc(loginStr, passwordStr, name.toStdString());
        _userRepo->NewUser();

        QMessageBox::information(this, "Успех", "Регистрация выполнена успешно!");
        _registrationSuccessful = true;
        //close();
        accept();
    }
    catch (const char* errorMsg) {
        QMessageBox::critical(this, "Ошибка", QString::fromUtf8(errorMsg));
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", QString::fromUtf8(e.what()));
    }
}

void RegistrationForm::on_buttonBox_rejected()
{
    //close();
    reject();
}

bool RegistrationForm::isRegistrationSuccessful() const
{
    return _registrationSuccessful;
}

Acc* RegistrationForm::getUser() const
{
    return _user;
}
