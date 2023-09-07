#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
#include<QDebug>

logindialog::logindialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);
    setWindowTitle("友缘通聊 v1.2");
}

logindialog::~logindialog()
{
    delete ui;
}

void logindialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    Q_EMIT SIG_closeLog();
}

void logindialog::on_log_clear_clicked()
{
    ui->le_log_tel->setText("");
    ui->le_log_pwd->setText("");
}


void logindialog::on_log_pb_clicked()
{
    QString tel=ui->le_log_tel->text();
    QString pwd=ui->le_log_pwd->text();
    QString temp_tel=tel;
    QString temp_pwd=pwd;
    if(tel.isEmpty()||pwd.isEmpty()||temp_tel.remove(" ").isEmpty()||temp_pwd.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","输入内容非法");
        return;
    }
    //1.检验tel是否符合标准
    if(tel.size()!=11)
    {
        QMessageBox::about(this,"提示","电话位数非法");
        return ;
    }
    //是否匹配  开头13 15 16 17 18 19
    QRegExp exp("^1[356789][0-9]\{9\}$");
    bool res=exp.exactMatch(tel);
    if(!res)
    {
        QMessageBox::about(this,"提示","电话号码非法");
        return ;
    }

    //2.检验pwd是否符合标准
    if(pwd.size()<7&&pwd.size()>15)
    {
        QMessageBox::about(this,"提示","密码位数非法");
        return;
    }

    //3.把用户内容输入发给kernel
    Q_EMIT SIG_LogCommit(tel,pwd);
}


void logindialog::on_log_pb_reg_clicked()
{
    QString tel=ui->le_reg_tel->text();
    QString name=ui->le_reg_name->text();
    QString pwd=ui->le_reg_pwd->text();

    QString temp_tel=tel;
    QString temp_name=name;
    QString temp_pwd=pwd;
    if(tel.isEmpty()||name.isEmpty()||pwd.isEmpty()
            ||temp_tel.remove(" ").isEmpty()||temp_pwd.remove(" ").isEmpty()||temp_name.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","输入非法");
        return;
    }

    //判断字符串长度
    if(tel.length()!=11||pwd.size()>15||pwd.size()<7||name.size()>10)
    {
        QMessageBox::about(this,"提示","输入长度非法");
        return;
    }

    //判断密码是否仅字母或者数字,电话号码开头是1
    QRegExp exp_tel("^1[356789][0-9]\{9\}$");
    bool res_tel=exp_tel.exactMatch(tel);
    if(!res_tel)
    {
        QMessageBox::about(this,"提示","电话号码非法");
        return;
    }
    QRegExp exp_pwd("^\(?![0-9]+$\)\(?![a-zA-Z]+$\)[0-9A-Za-z]\{6,14\}$");
    bool res_pwd=exp_pwd.exactMatch(pwd);
    if(!res_pwd)
    {
        QMessageBox::about(this,"提示","密码必须由数字、字母两种字符组成，长度在6-14位之间");
        return;
    }
    //3.发给kernel
    Q_EMIT SIG_registerCommit(tel,name,pwd);
}


void logindialog::on_log_clear_reg_clicked()
{
    ui->le_reg_name->setText("");
    ui->le_reg_pwd->setText("");
    ui->le_reg_tel->setText("");
}

