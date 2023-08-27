#ifndef CHATUSERINFO_H
#define CHATUSERINFO_H

#include <QWidget>

namespace Ui {
class Chatuserinfo;
}

class Chatuserinfo : public QWidget
{
    Q_OBJECT
private:
    int m_iconid;
    int m_id;//窗口id
public:
    QString m_name;//用于昵称对比
public:
    void setInfo(QString name, int iconid,int id);
public:
    explicit Chatuserinfo(QWidget *parent = nullptr);
    ~Chatuserinfo();


private slots:
    void on_pb_icon_clicked();

private:
    Ui::Chatuserinfo *ui;

signals:
    void SIG_showOurChatDlg(int m_id);
};

#endif // CHATUSERINFO_H
