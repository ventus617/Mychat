#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
#include<QCloseEvent>
#include"friendselect.h"
#include"ourchatselect.h"

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

public:
    void set_content(QString content);

    void setWindowInfo(QString name, int ID);

    void IfOffline();

    void closeEvent(QCloseEvent* event);
private:
    Ui::chatdialog *ui;
    //保存当前窗口的id和name，name用与查找，id用与查找当前窗口
    int m_id;
    QString m_name;
    ourchatselect* m_select;

signals:
    void SIG_SendMsg(int m_id,QString content);

    void SIG_getSelect();
    void SIG_SendFile(int m_id, QString fileName);
    void SIG_pauseFile(int id);
};

#endif // CHATDIALOG_H
