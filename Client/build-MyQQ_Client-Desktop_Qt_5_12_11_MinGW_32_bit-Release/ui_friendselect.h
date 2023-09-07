/********************************************************************************
** Form generated from reading UI file 'friendselect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDSELECT_H
#define UI_FRIENDSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_friendselect
{
public:
    QCheckBox *checkBox;

    void setupUi(QWidget *friendselect)
    {
        if (friendselect->objectName().isEmpty())
            friendselect->setObjectName(QString::fromUtf8("friendselect"));
        friendselect->resize(300, 20);
        friendselect->setMinimumSize(QSize(300, 20));
        friendselect->setMaximumSize(QSize(300, 20));
        checkBox = new QCheckBox(friendselect);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(0, 0, 380, 20));
        checkBox->setMinimumSize(QSize(380, 20));
        checkBox->setMaximumSize(QSize(380, 20));

        retranslateUi(friendselect);

        QMetaObject::connectSlotsByName(friendselect);
    } // setupUi

    void retranslateUi(QWidget *friendselect)
    {
        friendselect->setWindowTitle(QApplication::translate("friendselect", "Form", nullptr));
        checkBox->setText(QApplication::translate("friendselect", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class friendselect: public Ui_friendselect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDSELECT_H
