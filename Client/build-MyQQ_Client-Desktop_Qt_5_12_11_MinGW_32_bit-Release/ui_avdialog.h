/********************************************************************************
** Form generated from reading UI file 'avdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AVDIALOG_H
#define UI_AVDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "usershow.h"

QT_BEGIN_NAMESPACE

class Ui_avdialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *wd_top;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lb_title;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_small;
    QPushButton *pb_max;
    QPushButton *pb_close;
    UserShow *wd_big;
    UserShow *wd_small;
    QWidget *wd_bottle;
    QHBoxLayout *horizontalLayout;
    QCheckBox *qc_audio;
    QCheckBox *qc_video;

    void setupUi(QDialog *avdialog)
    {
        if (avdialog->objectName().isEmpty())
            avdialog->setObjectName(QString::fromUtf8("avdialog"));
        avdialog->resize(519, 431);
        verticalLayout = new QVBoxLayout(avdialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wd_top = new QWidget(avdialog);
        wd_top->setObjectName(QString::fromUtf8("wd_top"));
        wd_top->setMinimumSize(QSize(501, 31));
        wd_top->setMaximumSize(QSize(16777215, 31));
        horizontalLayout_2 = new QHBoxLayout(wd_top);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lb_title = new QLabel(wd_top);
        lb_title->setObjectName(QString::fromUtf8("lb_title"));

        horizontalLayout_2->addWidget(lb_title);

        horizontalSpacer = new QSpacerItem(348, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pb_small = new QPushButton(wd_top);
        pb_small->setObjectName(QString::fromUtf8("pb_small"));
        pb_small->setMinimumSize(QSize(21, 21));
        pb_small->setMaximumSize(QSize(21, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\271\274\345\234\206"));
        font.setPointSize(10);
        font.setBold(false);
        font.setWeight(50);
        pb_small->setFont(font);
        pb_small->setFlat(true);

        horizontalLayout_2->addWidget(pb_small);

        pb_max = new QPushButton(wd_top);
        pb_max->setObjectName(QString::fromUtf8("pb_max"));
        pb_max->setMinimumSize(QSize(21, 21));
        pb_max->setMaximumSize(QSize(21, 21));
        pb_max->setFont(font);
        pb_max->setFlat(true);

        horizontalLayout_2->addWidget(pb_max);

        pb_close = new QPushButton(wd_top);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setMinimumSize(QSize(21, 21));
        pb_close->setMaximumSize(QSize(21, 21));
        pb_close->setFont(font);
        pb_close->setFlat(true);

        horizontalLayout_2->addWidget(pb_close);


        verticalLayout->addWidget(wd_top);

        wd_big = new UserShow(avdialog);
        wd_big->setObjectName(QString::fromUtf8("wd_big"));
        wd_big->setMinimumSize(QSize(0, 341));
        wd_small = new UserShow(wd_big);
        wd_small->setObjectName(QString::fromUtf8("wd_small"));
        wd_small->setGeometry(QRect(350, 0, 141, 111));
        wd_small->setMinimumSize(QSize(141, 111));
        wd_small->setMaximumSize(QSize(141, 111));

        verticalLayout->addWidget(wd_big);

        wd_bottle = new QWidget(avdialog);
        wd_bottle->setObjectName(QString::fromUtf8("wd_bottle"));
        wd_bottle->setMinimumSize(QSize(501, 29));
        wd_bottle->setMaximumSize(QSize(16777215, 29));
        horizontalLayout = new QHBoxLayout(wd_bottle);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        qc_audio = new QCheckBox(wd_bottle);
        qc_audio->setObjectName(QString::fromUtf8("qc_audio"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qc_audio->sizePolicy().hasHeightForWidth());
        qc_audio->setSizePolicy(sizePolicy);
        qc_audio->setMinimumSize(QSize(97, 16));
        qc_audio->setMaximumSize(QSize(97, 16));
        qc_audio->setInputMethodHints(Qt::ImhNone);
        qc_audio->setChecked(false);

        horizontalLayout->addWidget(qc_audio);

        qc_video = new QCheckBox(wd_bottle);
        qc_video->setObjectName(QString::fromUtf8("qc_video"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(qc_video->sizePolicy().hasHeightForWidth());
        qc_video->setSizePolicy(sizePolicy1);
        qc_video->setMinimumSize(QSize(96, 16));
        qc_video->setMaximumSize(QSize(96, 16));

        horizontalLayout->addWidget(qc_video);


        verticalLayout->addWidget(wd_bottle);


        retranslateUi(avdialog);

        QMetaObject::connectSlotsByName(avdialog);
    } // setupUi

    void retranslateUi(QDialog *avdialog)
    {
        avdialog->setWindowTitle(QApplication::translate("avdialog", "Dialog", nullptr));
        lb_title->setText(QApplication::translate("avdialog", "\350\247\206\351\242\221\344\270\255", nullptr));
        pb_small->setText(QApplication::translate("avdialog", "\344\270\200", nullptr));
        pb_max->setText(QApplication::translate("avdialog", "\345\217\243", nullptr));
        pb_close->setText(QApplication::translate("avdialog", "X", nullptr));
        qc_audio->setText(QApplication::translate("avdialog", "\351\237\263\351\242\221", nullptr));
        qc_video->setText(QApplication::translate("avdialog", "\350\247\206\351\242\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class avdialog: public Ui_avdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AVDIALOG_H
