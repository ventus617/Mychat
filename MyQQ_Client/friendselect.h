#ifndef FRIENDSELECT_H
#define FRIENDSELECT_H

#include <QWidget>

namespace Ui {
class friendselect;
}

class friendselect : public QWidget
{
    Q_OBJECT

public:
    explicit friendselect(QWidget *parent = nullptr);
    ~friendselect();
public:
    void setinfo(int id,QString name);
    void setCheck(int status);
private slots:
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::friendselect *ui;
public:
    int m_id;
    QString m_name;
signals:
    void SIG_CheckFriend(int m_id);
};

#endif // FRIENDSELECT_H
