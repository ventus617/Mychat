#include "userinfo.h"
#include "ui_userinfo.h"
#include "config.h"
#include<QBitmap>
#include<QDebug>

userinfo::userinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userinfo)
{
    ui->setupUi(this);
}

userinfo::~userinfo()
{
    delete ui;
}

void userinfo::setInfo(QString name, QString lable, int iconid,int status,int id)
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
    if(m_status==status_offline)
    {
        QBitmap bmap;
        bmap.load(iconPath);
        ui->pb_icon->setIcon(bmap);
    }
    else
    {
        ui->pb_icon->setIcon(QIcon(iconPath));
    }
    //重绘
    this->repaint();
}

void userinfo::setUseroffline()
{
    m_status=status_offline;
    QString iconPath =QString(":./tx/%1.png").arg(m_iconid);
    QBitmap bmap;
    bmap.load(iconPath);
    ui->pb_icon->setIcon(bmap);
    this->repaint();
}

QString userinfo::getMyName()
{
    return m_name;
}


void userinfo::on_pb_icon_clicked()
{
    Q_EMIT SIG_showChatDlg(m_id);
}

