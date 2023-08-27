#include "chatuserinfo.h"
#include "ui_chatuserinfo.h"

void Chatuserinfo::setInfo(QString name, int iconid, int id)
{
    //1.保存好友的属性
    m_id=id;
    m_iconid=iconid;
    m_name=name;
    //2.设置控件
    ui->lb_name->setText(name);
    QString iconPath= QString(":./tx/%1.png").arg(m_iconid);
    ui->pb_icon->setIcon(QIcon(iconPath));
    //重绘
    this->repaint();
}

Chatuserinfo::Chatuserinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chatuserinfo)
{
    ui->setupUi(this);
}

Chatuserinfo::~Chatuserinfo()
{
    delete ui;
}

void Chatuserinfo::on_pb_icon_clicked()
{
    Q_EMIT SIG_showOurChatDlg(m_id);
}

