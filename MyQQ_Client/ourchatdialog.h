#ifndef OURCHATDIALOG_H
#define OURCHATDIALOG_H

#include <QWidget>
#include <QVBoxLayout>
#include"ourchatuserinfo.h"

namespace Ui {
class Ourchatdialog;
}

class Ourchatdialog : public QWidget
{
    Q_OBJECT

public:
    explicit Ourchatdialog(QWidget *parent = nullptr);
    ~Ourchatdialog();

public:
    void addMember(ourchatuserinfo* item);
    void set_content(QString content,QString m_name);
private slots:
    void on_pb_commit_clicked();

public:
    void getMyId(int id);

signals:
    void SIG_Our_SendMsg(int m_id,QString content);


private:
    Ui::Ourchatdialog *ui;
    QVBoxLayout* m_layout;//垂直布局的画布
    int m_id;
};

#endif // OURCHATDIALOG_H
