#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <memory.h>
#include "Database.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::shared_ptr<Database> dbPtr = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *createClient(std::shared_ptr<Database> dbPtr = nullptr);
    static int kInstanceCount;
private slots:
    void on_messagLineEdit_returnPressed();
    void on_sendMessageButton_clicked();
    void on_privateMessageSendButton_clicked();
    void on_actionOpen_another_client_triggered();
    void on_actionclose_client_triggered();
    void on_actionadd_new_client_triggered();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // MAINWINDOW_H
