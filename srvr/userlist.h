#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>

namespace Ui {
class userList;
}

class userList : public QWidget
{
    Q_OBJECT

public:
    explicit userList(QWidget *parent = nullptr);
    ~userList();

private:
    Ui::userList *ui;
};

#endif // USERLIST_H
