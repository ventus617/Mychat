/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatdialog
{
public:
    QTextBrowser *tb_chat;
    QTextEdit *te_chat;
    QPushButton *pb_commit;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pb_file;
    QPushButton *pb_talk;
    QPushButton *pb_ourchat;
    QPushButton *pb_file_pause;
    QPushButton *pb_morechat;

    void setupUi(QWidget *chatdialog)
    {
        if (chatdialog->objectName().isEmpty())
            chatdialog->setObjectName(QString::fromUtf8("chatdialog"));
        chatdialog->resize(500, 350);
        chatdialog->setMinimumSize(QSize(500, 350));
        chatdialog->setMaximumSize(QSize(500, 350));
        tb_chat = new QTextBrowser(chatdialog);
        tb_chat->setObjectName(QString::fromUtf8("tb_chat"));
        tb_chat->setGeometry(QRect(0, 20, 400, 180));
        te_chat = new QTextEdit(chatdialog);
        te_chat->setObjectName(QString::fromUtf8("te_chat"));
        te_chat->setGeometry(QRect(0, 250, 400, 70));
        pb_commit = new QPushButton(chatdialog);
        pb_commit->setObjectName(QString::fromUtf8("pb_commit"));
        pb_commit->setGeometry(QRect(330, 320, 70, 25));
        layoutWidget = new QWidget(chatdialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 210, 347, 31));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pb_file = new QPushButton(layoutWidget);
        pb_file->setObjectName(QString::fromUtf8("pb_file"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/folders.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_file->setIcon(icon);

        gridLayout->addWidget(pb_file, 0, 0, 1, 1);

        pb_talk = new QPushButton(layoutWidget);
        pb_talk->setObjectName(QString::fromUtf8("pb_talk"));

        gridLayout->addWidget(pb_talk, 0, 2, 1, 1);

        pb_ourchat = new QPushButton(layoutWidget);
        pb_ourchat->setObjectName(QString::fromUtf8("pb_ourchat"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/1.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pb_ourchat->setIcon(icon1);

        gridLayout->addWidget(pb_ourchat, 0, 3, 1, 1);

        pb_file_pause = new QPushButton(layoutWidget);
        pb_file_pause->setObjectName(QString::fromUtf8("pb_file_pause"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_file_pause->setIcon(icon2);

        gridLayout->addWidget(pb_file_pause, 0, 1, 1, 1);

        pb_morechat = new QPushButton(chatdialog);
        pb_morechat->setObjectName(QString::fromUtf8("pb_morechat"));
        pb_morechat->setGeometry(QRect(410, 20, 75, 23));

        retranslateUi(chatdialog);

        QMetaObject::connectSlotsByName(chatdialog);
    } // setupUi

    void retranslateUi(QWidget *chatdialog)
    {
        chatdialog->setWindowTitle(QApplication::translate("chatdialog", "Form", nullptr));
        pb_commit->setText(QApplication::translate("chatdialog", "\345\217\221\351\200\201", nullptr));
        pb_file->setText(QApplication::translate("chatdialog", "\346\226\207\344\273\266\344\274\240\350\276\223", nullptr));
        pb_talk->setText(QApplication::translate("chatdialog", "\351\237\263\351\242\221\351\200\232\350\257\235", nullptr));
        pb_ourchat->setText(QApplication::translate("chatdialog", "\345\273\272\347\253\213\347\276\244\350\201\212", nullptr));
        pb_file_pause->setText(QApplication::translate("chatdialog", "\346\232\202\345\201\234\344\274\240\350\276\223", nullptr));
        pb_morechat->setText(QApplication::translate("chatdialog", "\346\233\264\345\244\232\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatdialog: public Ui_chatdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
