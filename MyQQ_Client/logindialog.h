#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QWidget>
#include<QCloseEvent>

namespace Ui {
class logindialog;
}

class logindialog : public QWidget
{
    Q_OBJECT

public:
    explicit logindialog(QWidget *parent = nullptr);
    ~logindialog();
public:
    //重写父类的关闭窗口
    void closeEvent(QCloseEvent*event);
private slots:
    void on_log_clear_clicked();

    void on_log_pb_clicked();

    void on_log_pb_reg_clicked();

    void on_log_clear_reg_clicked();

private:
    Ui::logindialog *ui;
signals:
    //把注册界面的用户输入内容发kernel
    void SIG_registerCommit(QString tel,QString name,QString password);
    //把登录界面的用户输入内容发给kernel
    void SIG_LogCommit(QString tel,QString password);
    //给kernel发送关闭登录窗口的信号
    void SIG_closeLog();
};

#endif // LOGINDIALOG_H
