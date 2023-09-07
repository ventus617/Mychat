/********************************************************************************
** Form generated from reading UI file 'ourchatselect.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OURCHATSELECT_H
#define UI_OURCHATSELECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ourchatselect
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *our_wdg;
    QSpacerItem *verticalSpacer;
    QPushButton *pb_commit;

    void setupUi(QWidget *ourchatselect)
    {
        if (ourchatselect->objectName().isEmpty())
            ourchatselect->setObjectName(QString::fromUtf8("ourchatselect"));
        ourchatselect->resize(399, 400);
        ourchatselect->setMinimumSize(QSize(1, 1));
        ourchatselect->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        ourchatselect->setFont(font);
        ourchatselect->setLayoutDirection(Qt::LeftToRight);
        tabWidget = new QTabWidget(ourchatselect);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 400, 400));
        tabWidget->setMinimumSize(QSize(1, 1));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        scrollArea = new QScrollArea(tab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 391, 331));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 389, 329));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        our_wdg = new QWidget(scrollAreaWidgetContents);
        our_wdg->setObjectName(QString::fromUtf8("our_wdg"));

        verticalLayout->addWidget(our_wdg);

        verticalSpacer = new QSpacerItem(20, 312, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);
        pb_commit = new QPushButton(tab);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(321, 335, 71, 31));
        tabWidget->addTab(tab, QString());

        retranslateUi(ourchatselect);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ourchatselect);
    } // setupUi

    void retranslateUi(QWidget *ourchatselect)
    {
        ourchatselect->setWindowTitle(QApplication::translate("ourchatselect", "Form", nullptr));
        pb_commit->setText(QApplication::translate("ourchatselect", "\347\241\256\350\256\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ourchatselect", "  \345\245\275\345\217\213\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ourchatselect: public Ui_ourchatselect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OURCHATSELECT_H
