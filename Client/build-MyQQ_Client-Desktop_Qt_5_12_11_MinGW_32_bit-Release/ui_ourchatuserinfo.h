/********************************************************************************
** Form generated from reading UI file 'ourchatuserinfo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OURCHATUSERINFO_H
#define UI_OURCHATUSERINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ourchatuserinfo
{
public:
    QPushButton *pb_icon;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *lb_lable;
    QLabel *lb_name;

    void setupUi(QWidget *ourchatuserinfo)
    {
        if (ourchatuserinfo->objectName().isEmpty())
            ourchatuserinfo->setObjectName(QString::fromUtf8("ourchatuserinfo"));
        ourchatuserinfo->resize(208, 37);
        ourchatuserinfo->setMinimumSize(QSize(208, 37));
        ourchatuserinfo->setMaximumSize(QSize(208, 37));
        pb_icon = new QPushButton(ourchatuserinfo);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(10, 0, 41, 31));
        pb_icon->setIconSize(QSize(41, 31));
        pb_icon->setFlat(true);
        widget = new QWidget(ourchatuserinfo);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 0, 141, 32));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lb_lable = new QLabel(widget);
        lb_lable->setObjectName(QString::fromUtf8("lb_lable"));

        gridLayout->addWidget(lb_lable, 2, 0, 1, 1);

        lb_name = new QLabel(widget);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));

        gridLayout->addWidget(lb_name, 1, 0, 1, 1);


        retranslateUi(ourchatuserinfo);

        QMetaObject::connectSlotsByName(ourchatuserinfo);
    } // setupUi

    void retranslateUi(QWidget *ourchatuserinfo)
    {
        ourchatuserinfo->setWindowTitle(QApplication::translate("ourchatuserinfo", "Form", nullptr));
        pb_icon->setText(QString());
        lb_lable->setText(QApplication::translate("ourchatuserinfo", "TextLabel", nullptr));
        lb_name->setText(QApplication::translate("ourchatuserinfo", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ourchatuserinfo: public Ui_ourchatuserinfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OURCHATUSERINFO_H
