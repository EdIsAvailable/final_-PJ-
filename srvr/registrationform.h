
#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include <QLineEdit>
#include "Acc.h"
#include "UserRepository.h"
#include <QDialog>

namespace Ui {
class RegistrationForm;
}

//class RegistrationForm : public QWidget
class RegistrationForm : public QDialog{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

    bool isRegistrationSuccessful() const;
    Acc* getUser() const;

private slots:
    void on_loginButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::RegistrationForm *ui;
    QLineEdit *nameEdit;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;
    UserRepository *_userRepo;
    Acc* _user = nullptr;
    bool _registrationSuccessful = false;
};

#endif // REGISTRATIONFORM_H
