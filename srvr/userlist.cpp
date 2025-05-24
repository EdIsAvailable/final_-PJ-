#include "userlist.h"
#include "ui_userlist.h"

userList::userList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userList)
{
    ui->setupUi(this);
}

userList::~userList()
{
    delete ui;
}
