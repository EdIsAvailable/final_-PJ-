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
    static MainWindow *createClient();
private slots:
    void on_messagLineEdit_returnPressed();
    void on_sendMessageButton_clicked();
    void on_privateMessageSendButton_clicked();
    void on_actionclose_client_triggered();
    void on_actionadd_new_client_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
