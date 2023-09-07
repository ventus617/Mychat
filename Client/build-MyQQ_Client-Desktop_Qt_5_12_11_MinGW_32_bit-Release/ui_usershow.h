/********************************************************************************
** Form generated from reading UI file 'usershow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSHOW_H
#define UI_USERSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserShow
{
public:

    void setupUi(QWidget *UserShow)
    {
        if (UserShow->objectName().isEmpty())
            UserShow->setObjectName(QString::fromUtf8("UserShow"));
        UserShow->resize(141, 111);
        UserShow->setMinimumSize(QSize(141, 111));
        UserShow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        retranslateUi(UserShow);

        QMetaObject::connectSlotsByName(UserShow);
    } // setupUi

    void retranslateUi(QWidget *UserShow)
    {
        UserShow->setWindowTitle(QApplication::translate("UserShow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserShow: public Ui_UserShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSHOW_H
