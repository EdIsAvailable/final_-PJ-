/********************************************************************************
** Form generated from reading UI file 'userlist.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERLIST_H
#define UI_USERLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userList
{
public:
    QListWidget *userListWidget;

    void setupUi(QWidget *userList)
    {
        if (userList->objectName().isEmpty())
            userList->setObjectName("userList");
        userList->resize(400, 300);
        userListWidget = new QListWidget(userList);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setGeometry(QRect(15, 31, 371, 251));

        retranslateUi(userList);

        QMetaObject::connectSlotsByName(userList);
    } // setupUi

    void retranslateUi(QWidget *userList)
    {
        userList->setWindowTitle(QCoreApplication::translate("userList", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userList: public Ui_userList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERLIST_H
