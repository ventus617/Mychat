/********************************************************************************
** Form generated from reading UI file 'chatuserinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATUSERINFO_H
#define UI_CHATUSERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chatuserinfo
{
public:
    QPushButton *pb_icon;
    QLabel *lb_name;

    void setupUi(QWidget *Chatuserinfo)
    {
        if (Chatuserinfo->objectName().isEmpty())
            Chatuserinfo->setObjectName(QString::fromUtf8("Chatuserinfo"));
        Chatuserinfo->resize(280, 60);
        Chatuserinfo->setMinimumSize(QSize(280, 60));
        Chatuserinfo->setMaximumSize(QSize(280, 60));
        pb_icon = new QPushButton(Chatuserinfo);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(30, 10, 61, 41));
        pb_icon->setIconSize(QSize(61, 51));
        pb_icon->setFlat(true);
        lb_name = new QLabel(Chatuserinfo);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setGeometry(QRect(110, 10, 141, 41));

        retranslateUi(Chatuserinfo);

        QMetaObject::connectSlotsByName(Chatuserinfo);
    } // setupUi

    void retranslateUi(QWidget *Chatuserinfo)
    {
        Chatuserinfo->setWindowTitle(QApplication::translate("Chatuserinfo", "Form", nullptr));
        pb_icon->setText(QString());
        lb_name->setText(QApplication::translate("Chatuserinfo", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chatuserinfo: public Ui_Chatuserinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATUSERINFO_H
