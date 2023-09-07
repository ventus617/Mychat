/********************************************************************************
** Form generated from reading UI file 'userinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINFO_H
#define UI_USERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_userinfo
{
public:
    QPushButton *pb_icon;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lb_name;
    QLabel *lb_lable;

    void setupUi(QWidget *userinfo)
    {
        if (userinfo->objectName().isEmpty())
            userinfo->setObjectName(QString::fromUtf8("userinfo"));
        userinfo->resize(280, 60);
        userinfo->setMinimumSize(QSize(280, 60));
        userinfo->setMaximumSize(QSize(280, 60));
        pb_icon = new QPushButton(userinfo);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(10, 0, 71, 51));
        pb_icon->setIconSize(QSize(60, 40));
        pb_icon->setFlat(true);
        widget = new QWidget(userinfo);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(90, 0, 171, 51));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lb_name = new QLabel(widget);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));

        verticalLayout->addWidget(lb_name);

        lb_lable = new QLabel(widget);
        lb_lable->setObjectName(QString::fromUtf8("lb_lable"));

        verticalLayout->addWidget(lb_lable);


        retranslateUi(userinfo);

        QMetaObject::connectSlotsByName(userinfo);
    } // setupUi

    void retranslateUi(QWidget *userinfo)
    {
        userinfo->setWindowTitle(QApplication::translate("userinfo", "Form", nullptr));
        pb_icon->setText(QString());
        lb_name->setText(QApplication::translate("userinfo", "\347\224\250\346\210\267\345\220\215", nullptr));
        lb_lable->setText(QApplication::translate("userinfo", "\347\255\276\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userinfo: public Ui_userinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINFO_H
