#include "ourchatselect.h"
#include "ui_ourchatselect.h"
#include<QMessageBox>
#include<QDebug>

ourchatselect::ourchatselect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ourchatselect)
{
    ui->setupUi(this);
     setWindowTitle("好友选择");
    //new 一个垂直布局的画布
    m_layout=new QVBoxLayout;
    //设置上下左右距离外边框的间距
    m_layout->setContentsMargins(0,0,0,0);
    //设置画布上每个控件的距离
    m_layout->setSpacing(4);
    //把画布设置到控件上
    ui->our_wdg->setLayout(m_layout);
}

ourchatselect::~ourchatselect()
{
    delete ui;
}

void ourchatselect::addinfo(friendselect *item)
{
    qDebug()<<__func__;
    m_layout->addWidget(item);
    m_friendSet.insert(item);
}

void ourchatselect::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->hide();
}

void ourchatselect::slot_deal_checkBox(int id)
{
    qDebug()<<__func__;
    m_set.insert(id);
}


void ourchatselect::on_pb_commit_clicked()
{
    qDebug()<<__func__;
    for(auto ite=m_friendSet.begin();ite!=m_friendSet.end();ite++)
    {
        (*ite)->setCheck(0);//取消勾选
    }
    this->hide();
    SIG_SendSelect(&m_set);
}

