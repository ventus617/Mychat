/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pb_start;
    QPushButton *pb_pause;
    QPushButton *pb_video_pause;
    QPushButton *pb_video_start;
    QLabel *lb_show;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(668, 340);
        pb_start = new QPushButton(Dialog);
        pb_start->setObjectName(QString::fromUtf8("pb_start"));
        pb_start->setGeometry(QRect(70, 40, 131, 71));
        pb_pause = new QPushButton(Dialog);
        pb_pause->setObjectName(QString::fromUtf8("pb_pause"));
        pb_pause->setGeometry(QRect(330, 40, 121, 71));
        pb_video_pause = new QPushButton(Dialog);
        pb_video_pause->setObjectName(QString::fromUtf8("pb_video_pause"));
        pb_video_pause->setGeometry(QRect(450, 40, 121, 71));
        pb_video_start = new QPushButton(Dialog);
        pb_video_start->setObjectName(QString::fromUtf8("pb_video_start"));
        pb_video_start->setGeometry(QRect(200, 40, 131, 71));
        lb_show = new QLabel(Dialog);
        lb_show->setObjectName(QString::fromUtf8("lb_show"));
        lb_show->setGeometry(QRect(100, 140, 461, 171));
        lb_show->setScaledContents(true);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        pb_start->setText(QApplication::translate("Dialog", "\345\274\200\345\247\213", nullptr));
        pb_pause->setText(QApplication::translate("Dialog", "\346\232\202\345\201\234", nullptr));
        pb_video_pause->setText(QApplication::translate("Dialog", "\350\247\206\351\242\221\346\232\202\345\201\234", nullptr));
        pb_video_start->setText(QApplication::translate("Dialog", "\350\247\206\351\242\221\345\274\200\345\247\213", nullptr));
        lb_show->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
