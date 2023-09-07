/********************************************************************************
** Form generated from reading UI file 'myui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYUI_H
#define UI_MYUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myUI
{
public:
    QPushButton *pb_icon;
    QLineEdit *le_lable;
    QLabel *lb_name;
    QTabWidget *tabWidget;
    QWidget *tab_friend;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QWidget *wdg_friend;
    QSpacerItem *verticalSpacer;
    QWidget *tab_ourchat;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_6;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_ourchat;
    QSpacerItem *verticalSpacer_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pb_menu;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *myUI)
    {
        if (myUI->objectName().isEmpty())
            myUI->setObjectName(QString::fromUtf8("myUI"));
        myUI->resize(300, 600);
        myUI->setMinimumSize(QSize(300, 600));
        myUI->setMaximumSize(QSize(300, 600));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        myUI->setFont(font);
        pb_icon = new QPushButton(myUI);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(10, 20, 60, 60));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tx/1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_icon->setIcon(icon);
        pb_icon->setIconSize(QSize(60, 60));
        pb_icon->setAutoDefault(true);
        pb_icon->setFlat(true);
        le_lable = new QLineEdit(myUI);
        le_lable->setObjectName(QString::fromUtf8("le_lable"));
        le_lable->setGeometry(QRect(110, 60, 161, 20));
        lb_name = new QLabel(myUI);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setGeometry(QRect(110, 30, 161, 16));
        tabWidget = new QTabWidget(myUI);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 90, 301, 471));
        tab_friend = new QWidget();
        tab_friend->setObjectName(QString::fromUtf8("tab_friend"));
        scrollArea = new QScrollArea(tab_friend);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(-1, -1, 301, 441));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 299, 439));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wdg_friend = new QWidget(scrollAreaWidgetContents_2);
        wdg_friend->setObjectName(QString::fromUtf8("wdg_friend"));

        verticalLayout->addWidget(wdg_friend);

        verticalSpacer = new QSpacerItem(20, 402, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents_2);
        tabWidget->addTab(tab_friend, QString());
        tab_ourchat = new QWidget();
        tab_ourchat->setObjectName(QString::fromUtf8("tab_ourchat"));
        scrollArea_2 = new QScrollArea(tab_ourchat);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(-1, -1, 301, 441));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 299, 439));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        wdg_ourchat = new QWidget(scrollAreaWidgetContents_6);
        wdg_ourchat->setObjectName(QString::fromUtf8("wdg_ourchat"));

        verticalLayout_2->addWidget(wdg_ourchat);

        verticalSpacer_2 = new QSpacerItem(20, 402, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_6);
        tabWidget->addTab(tab_ourchat, QString());
        layoutWidget = new QWidget(myUI);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 560, 134, 31));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pb_menu = new QPushButton(layoutWidget);
        pb_menu->setObjectName(QString::fromUtf8("pb_menu"));

        gridLayout->addWidget(pb_menu, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 0, 1, 1, 1);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout->addWidget(pushButton_4, 0, 2, 1, 1);

        layoutWidget->raise();
        tabWidget->raise();
        pb_icon->raise();
        le_lable->raise();
        lb_name->raise();

        retranslateUi(myUI);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(myUI);
    } // setupUi

    void retranslateUi(QWidget *myUI)
    {
        myUI->setWindowTitle(QApplication::translate("myUI", "Form", nullptr));
        pb_icon->setText(QString());
        le_lable->setText(QApplication::translate("myUI", "\350\277\231\346\230\257\344\270\200\344\270\252\347\245\236\345\245\207\347\232\204\344\272\213\346\203\205...", nullptr));
        lb_name->setText(QApplication::translate("myUI", "\346\236\227\351\227\264\344\271\235\345\260\276", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_friend), QApplication::translate("myUI", "\345\245\275\345\217\213\345\210\227\350\241\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_ourchat), QApplication::translate("myUI", "\347\276\244\350\201\212", nullptr));
        pb_menu->setText(QString());
        pushButton_3->setText(QString());
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class myUI: public Ui_myUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYUI_H
