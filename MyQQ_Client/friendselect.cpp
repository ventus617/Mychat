#include "friendselect.h"
#include "ui_friendselect.h"
#include<QDebug>

friendselect::friendselect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendselect)
{
    ui->setupUi(this);

}

friendselect::~friendselect()
{
    delete ui;
}

void friendselect::setinfo(int id, QString name)
{
    m_id=id;
    m_name=name;
    ui->checkBox->setText(m_name);
    this->repaint();
}

void friendselect::setCheck(int status)
{
    ui->checkBox->setChecked(status);
}

void friendselect::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        Q_EMIT SIG_CheckFriend(m_id);
    }
}

