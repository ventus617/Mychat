#ifndef USERSHOW_H
#define USERSHOW_H

#include <QWidget>
#include <QPaintEvent>
namespace Ui {
class UserShow;
}

class UserShow : public QWidget
{
    Q_OBJECT

public:
    explicit UserShow(QWidget *parent = nullptr);
    ~UserShow();
    void paintEvent(QPaintEvent *event);
    void setinfo(int id);
    void slot_setImage(QImage&img);

private:
    Ui::UserShow *ui;
    QImage m_img;
    int m_id;
    friend class avdialog;
};

#endif // USERSHOW_H
