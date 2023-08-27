#ifndef OURCHAT_H
#define OURCHAT_H

#include <QWidget>

namespace Ui {
class ourchat;
}

class ourchat : public QWidget
{
    Q_OBJECT

public:
    explicit ourchat(QWidget *parent = nullptr);
    ~ourchat();

private:
    Ui::ourchat *ui;
};

#endif // OURCHAT_H
