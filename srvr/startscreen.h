
#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include "Acc.h"

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

    Acc* getLoggedUser() const;
    void setLoggedUser(Acc* user);

private slots:
    void onLoginClicked();
    void onRegisterClicked();

private:
    Ui::StartScreen *ui;
    Acc* _loggedUser = nullptr;
};

#endif // STARTSCREEN_H
