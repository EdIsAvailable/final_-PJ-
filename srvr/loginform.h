/*
#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_registrationPushButton_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
*/

#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QLineEdit>
#include "Acc.h"
#include "UserRepository.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

    bool isLoginSuccessful() const;
    Acc* getUser() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_registrationPushButton_clicked();

private:
    Ui::LoginForm *ui;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    UserRepository *_userRepo;
    Acc* _user = nullptr;
    bool _loginSuccessful = false;
};

#endif // LOGINFORM_H
