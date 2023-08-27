#ifndef OURCHATUSERINFO_H
#define OURCHATUSERINFO_H

#include <QWidget>
#include"config.h"
namespace Ui {
class ourchatuserinfo;
}

class ourchatuserinfo : public QWidget
{
    Q_OBJECT
private:
    QString lable;
    int m_iconid;
    int m_status;//用户状态
    int m_id;//用户id
public:
    QString m_name;//用于昵称对比

public:
    explicit ourchatuserinfo(QWidget *parent = nullptr);
    ~ourchatuserinfo();
public:
    // 设置好友属性和控件内容
    void setInfo(QString name, QString lable, int iconid,int status,int id);
    // 设置用户为下线状态
    void setUserOffline();
private:
    Ui::ourchatuserinfo *ui;


signals:
private slots:
};

#endif // OURCHATUSERINFO_H
