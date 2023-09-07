/********************************************************************************
** Form generated from reading UI file 'ourchatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OURCHATDIALOG_H
#define UI_OURCHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ourchatdialog
{
public:
    QTextEdit *textEdit;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *our_wdg;
    QSpacerItem *verticalSpacer;
    QTextBrowser *textBrowser;
    QPushButton *pb_commit;
    QPushButton *pb_getmore;

    void setupUi(QWidget *Ourchatdialog)
    {
        if (Ourchatdialog->objectName().isEmpty())
            Ourchatdialog->setObjectName(QString::fromUtf8("Ourchatdialog"));
        Ourchatdialog->resize(567, 346);
        Ourchatdialog->setMinimumSize(QSize(567, 346));
        Ourchatdialog->setMaximumSize(QSize(567, 346));
        textEdit = new QTextEdit(Ourchatdialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 210, 321, 101));
        scrollArea = new QScrollArea(Ourchatdialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(360, 10, 191, 321));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 189, 319));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        our_wdg = new QWidget(scrollAreaWidgetContents);
        our_wdg->setObjectName(QString::fromUtf8("our_wdg"));

        verticalLayout->addWidget(our_wdg);

        verticalSpacer = new QSpacerItem(20, 282, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);
        textBrowser = new QTextBrowser(Ourchatdialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 321, 181));
        pb_commit = new QPushButton(Ourchatdialog);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(256, 320, 75, 21));
        pb_getmore = new QPushButton(Ourchatdialog);
        pb_getmore->setObjectName(QString::fromUtf8("pb_getmore"));
        pb_getmore->setGeometry(QRect(10, 320, 75, 21));

        retranslateUi(Ourchatdialog);

        QMetaObject::connectSlotsByName(Ourchatdialog);
    } // setupUi

    void retranslateUi(QWidget *Ourchatdialog)
    {
        Ourchatdialog->setWindowTitle(QApplication::translate("Ourchatdialog", "Form", nullptr));
        pb_commit->setText(QApplication::translate("Ourchatdialog", "\345\217\221\351\200\201", nullptr));
        pb_getmore->setText(QApplication::translate("Ourchatdialog", "\346\233\264\345\244\232\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Ourchatdialog: public Ui_Ourchatdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OURCHATDIALOG_H
