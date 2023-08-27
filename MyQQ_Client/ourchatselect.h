#ifndef OURCHATSELECT_H
#define OURCHATSELECT_H

#include <QWidget>
#include<QVBoxLayout>
#include<QCloseEvent>
#include "friendselect.h"
#include"userinfo.h"
#include<QSet>
namespace Ui {
class ourchatselect;
}

class ourchatselect : public QWidget
{
    Q_OBJECT

public:
    explicit ourchatselect(QWidget *parent = nullptr);
    ~ourchatselect();

private:
    Ui::ourchatselect *ui;
    QVBoxLayout* m_layout;//垂直布局的画布
    //存放子类信息的容器
    QSet<int> m_set;
    //存放自己的组件
    QSet<friendselect*> m_friendSet;
public:
    void addinfo(friendselect* item);
    void closeEvent(QCloseEvent* event);

signals:
    void SIG_CheckYes();
    void SIG_SendSelect(QSet<int>* list);
private slots:
    //接收子类中QCheckBox的消息
    void slot_deal_checkBox(int id);
    void on_pb_commit_clicked();
};

#endif // OURCHATSELECT_H
