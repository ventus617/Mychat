#include "usershow.h"
#include "ui_usershow.h"
#include<QPainter>

UserShow::UserShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserShow)
{
    ui->setupUi(this);
}

UserShow::~UserShow()
{
    delete ui;
}

void UserShow::paintEvent(QPaintEvent *event)
{
    //画背景
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(-1,0,this->width()+1,this->height());
    if(m_img.size().height()<=0)return;
    //画人物
    //等比例缩放
    //Qt::IgnoreAspectRatio;
    m_img=m_img.scaled(this->width(),this->height(),Qt::KeepAspectRatio);
    QPixmap pix=QPixmap::fromImage(m_img);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    painter.end();

}

void UserShow::setinfo(int id)
{
    m_id=id;
}

void UserShow::slot_setImage(QImage &img)
{
    m_img=img;
    this->update();//触发重绘
}
