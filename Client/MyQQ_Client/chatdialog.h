#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
#include<QCloseEvent>
#include"friendselect.h"
#include"ourchatselect.h"
#include"avdialog.h"

namespace Ui {
class chatdialog;
}

class chatdialog : public QWidget
{
    Q_OBJECT

public:
    explicit chatdialog(QWidget *parent = nullptr);
    ~chatdialog();

private slots:
    void on_pb_file_clicked();

    void on_pb_talk_clicked();

    void on_pb_ourchat_clicked();

    void on_pb_commit_clicked();

    void on_pb_file_pause_clicked();

    void on_pb_morechat_clicked();
    void closeEvent(QCloseEvent* event);
public:
    void set_content(QString content,QString time);
    void set_Mycontent(QString content,QString time,int id);
    void setWindowInfo(QString name, int ID,int Userid);

    void IfOffline();


private:

    Ui::chatdialog *ui;
    ourchatselect* m_select;
    unsigned int m_num;
public:
    //保存当前窗口的id和name，name用与查找，id用与查找当前窗口,userid是用户的id,用于区分视频聊天的窗口
    int m_id,m_userid;  
    QString m_name;
    avdialog* m_call;

signals:
    void SIG_SendMsg(int m_id,QString content,QString time);
    void SIG_getSelect();
    void SIG_SendFile(int m_id, QString fileName);
    void SIG_pauseFile(int id);
    void SIG_GetMoreChat(int startnum,int endnum,int friendid);
    void SIG_TALK_RQ(int friendid);
};

#endif // CHATDIALOG_H
