#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>

namespace Ui {
class userinfo;
}

class userinfo : public QWidget
{
    Q_OBJECT

public:
    explicit userinfo(QWidget *parent = nullptr);
    ~userinfo();

private:
    Ui::userinfo *ui;
    QString lable;
    int m_iconid;
    int m_status;//用户状态
    int m_id;//用户id
public:
    QString m_name;//用于昵称对比
public:
    void setInfo(QString name, QString lable, int iconid,int status,int id);

    void setUseroffline();
    QString getMyName();
signals:
    void SIG_showChatDlg(int id);

private slots:
    void on_pb_icon_clicked();
};

#endif // USERINFO_H
