/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_logindialog
{
public:
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *lb_log_tel;
    QLineEdit *le_log_tel;
    QLabel *lb_log_pwd;
    QLineEdit *le_log_pwd;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *log_pb;
    QSpacerItem *horizontalSpacer;
    QPushButton *log_clear;
    QWidget *tab_2;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *log_pb_reg;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *log_clear_reg;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_2;
    QLabel *lb_reg_name;
    QLineEdit *le_reg_name;
    QLabel *lb_reg_tel;
    QLineEdit *le_reg_tel;
    QLabel *lb_reg_pwd;
    QLineEdit *le_reg_pwd;

    void setupUi(QWidget *logindialog)
    {
        if (logindialog->objectName().isEmpty())
            logindialog->setObjectName(QString::fromUtf8("logindialog"));
        logindialog->resize(600, 400);
        logindialog->setMinimumSize(QSize(600, 400));
        logindialog->setMaximumSize(QSize(600, 400));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        logindialog->setFont(font);
        label = new QLabel(logindialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 250, 400));
        label->setMinimumSize(QSize(250, 400));
        label->setMaximumSize(QSize(250, 400));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/register.png")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        tabWidget = new QTabWidget(logindialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(250, 0, 350, 400));
        tabWidget->setMinimumSize(QSize(350, 400));
        tabWidget->setMaximumSize(QSize(350, 400));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 60, 221, 101));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lb_log_tel = new QLabel(layoutWidget);
        lb_log_tel->setObjectName(QString::fromUtf8("lb_log_tel"));

        gridLayout->addWidget(lb_log_tel, 0, 0, 1, 1);

        le_log_tel = new QLineEdit(layoutWidget);
        le_log_tel->setObjectName(QString::fromUtf8("le_log_tel"));

        gridLayout->addWidget(le_log_tel, 0, 1, 1, 1);

        lb_log_pwd = new QLabel(layoutWidget);
        lb_log_pwd->setObjectName(QString::fromUtf8("lb_log_pwd"));

        gridLayout->addWidget(lb_log_pwd, 1, 0, 1, 1);

        le_log_pwd = new QLineEdit(layoutWidget);
        le_log_pwd->setObjectName(QString::fromUtf8("le_log_pwd"));
        le_log_pwd->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(le_log_pwd, 1, 1, 1, 1);

        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(60, 230, 221, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        log_pb = new QPushButton(layoutWidget1);
        log_pb->setObjectName(QString::fromUtf8("log_pb"));

        horizontalLayout->addWidget(log_pb);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        log_clear = new QPushButton(layoutWidget1);
        log_clear->setObjectName(QString::fromUtf8("log_clear"));

        horizontalLayout->addWidget(log_clear);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(60, 220, 221, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        log_pb_reg = new QPushButton(layoutWidget2);
        log_pb_reg->setObjectName(QString::fromUtf8("log_pb_reg"));

        horizontalLayout_2->addWidget(log_pb_reg);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        log_clear_reg = new QPushButton(layoutWidget2);
        log_clear_reg->setObjectName(QString::fromUtf8("log_clear_reg"));

        horizontalLayout_2->addWidget(log_clear_reg);

        layoutWidget3 = new QWidget(tab_2);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(60, 50, 221, 121));
        gridLayout_2 = new QGridLayout(layoutWidget3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lb_reg_name = new QLabel(layoutWidget3);
        lb_reg_name->setObjectName(QString::fromUtf8("lb_reg_name"));

        gridLayout_2->addWidget(lb_reg_name, 0, 0, 1, 1);

        le_reg_name = new QLineEdit(layoutWidget3);
        le_reg_name->setObjectName(QString::fromUtf8("le_reg_name"));
        le_reg_name->setEchoMode(QLineEdit::Normal);

        gridLayout_2->addWidget(le_reg_name, 0, 1, 1, 1);

        lb_reg_tel = new QLabel(layoutWidget3);
        lb_reg_tel->setObjectName(QString::fromUtf8("lb_reg_tel"));

        gridLayout_2->addWidget(lb_reg_tel, 1, 0, 1, 1);

        le_reg_tel = new QLineEdit(layoutWidget3);
        le_reg_tel->setObjectName(QString::fromUtf8("le_reg_tel"));

        gridLayout_2->addWidget(le_reg_tel, 1, 1, 1, 1);

        lb_reg_pwd = new QLabel(layoutWidget3);
        lb_reg_pwd->setObjectName(QString::fromUtf8("lb_reg_pwd"));

        gridLayout_2->addWidget(lb_reg_pwd, 2, 0, 1, 1);

        le_reg_pwd = new QLineEdit(layoutWidget3);
        le_reg_pwd->setObjectName(QString::fromUtf8("le_reg_pwd"));
        le_reg_pwd->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(le_reg_pwd, 2, 1, 1, 1);

        tabWidget->addTab(tab_2, QString());

        retranslateUi(logindialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(logindialog);
    } // setupUi

    void retranslateUi(QWidget *logindialog)
    {
        logindialog->setWindowTitle(QApplication::translate("logindialog", "Form", nullptr));
        label->setText(QString());
        lb_log_tel->setText(QApplication::translate("logindialog", "\347\224\265\350\257\235\357\274\232", nullptr));
        le_log_tel->setText(QApplication::translate("logindialog", "18228205746", nullptr));
        lb_log_pwd->setText(QApplication::translate("logindialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        le_log_pwd->setText(QApplication::translate("logindialog", "z9090900", nullptr));
        log_pb->setText(QApplication::translate("logindialog", "\347\231\273\345\275\225", nullptr));
        log_clear->setText(QApplication::translate("logindialog", " \346\270\205\347\251\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("logindialog", "\347\231\273\345\275\225", nullptr));
        log_pb_reg->setText(QApplication::translate("logindialog", "\346\263\250\345\206\214", nullptr));
        log_clear_reg->setText(QApplication::translate("logindialog", " \346\270\205\347\251\272", nullptr));
        lb_reg_name->setText(QApplication::translate("logindialog", "\346\230\265\347\247\260\357\274\232", nullptr));
        le_reg_name->setText(QApplication::translate("logindialog", "\346\236\227\351\227\264\344\271\235\345\260\276", nullptr));
        lb_reg_tel->setText(QApplication::translate("logindialog", "\347\224\265\350\257\235\357\274\232", nullptr));
        le_reg_tel->setText(QApplication::translate("logindialog", "18228205746", nullptr));
        lb_reg_pwd->setText(QApplication::translate("logindialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        le_reg_pwd->setText(QApplication::translate("logindialog", "z9090900", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("logindialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class logindialog: public Ui_logindialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
