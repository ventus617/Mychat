#include "ourchatuserinfo.h"
#include "ui_ourchatuserinfo.h"

ourchatuserinfo::ourchatuserinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ourchatuserinfo)
{
    ui->setupUi(this);
}

ourchatuserinfo::~ourchatuserinfo()
{
    delete ui;
}

void ourchatuserinfo::setInfo(QString name, QString lable, int iconid, int status, int id)
{
    //1.保存好友的属性
    m_id=id;
    m_status=status;
    m_iconid=iconid;
    m_name=name;
    //2.设置控件
    ui->lb_lable->setText(lable);
    ui->lb_name->setText(name);

    QString iconPath= QString(":./tx/%1.png").arg(m_iconid);
    ui->pb_icon->setIcon(QIcon(iconPath));
    //重绘
    this->repaint();
}



