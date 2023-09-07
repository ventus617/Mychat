#ifndef MYUI_H
#define MYUI_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QMenu>
#include"userinfo.h"
#include "chatuserinfo.h"
namespace Ui {
class myUI;
}

class myUI : public QWidget
{
    Q_OBJECT

public:
    explicit myUI(QWidget *parent = nullptr);
    ~myUI();

private slots:
    void on_pb_menu_clicked();

    void slot_deal_pb_Menu_Clicked(QAction*action);
public:
    void addFriend(userinfo* item);
    void setInfo(QString name,QString lable,int iconid);
    void addOurChat(Chatuserinfo* item);
    void closeEvent(QCloseEvent* event);

signals:
    void SIG_addFriend();
    void SIG_closeMyChatDlg();
    void SIG_deleteFriend();

private:
    Ui::myUI *ui;
    QVBoxLayout* m_layout;//垂直布局的画布
    QVBoxLayout* m_layout2;
    QMenu*m_menu;
};

#endif // MYUI_H
