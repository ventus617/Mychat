#include "myui.h"
#include "ui_myui.h"
#include<QMessageBox>

myUI::myUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myUI)
{
    ui->setupUi(this);
    setWindowTitle(QString("MyQQ"));

    //new 一个垂直布局的画布
    m_layout=new QVBoxLayout;
    m_layout2=new QVBoxLayout;
    //设置上下左右距离外边框的间距
    m_layout->setContentsMargins(0,0,0,0);
    m_layout2->setContentsMargins(0,0,0,0);
    //设置画布上每个控件的距离
    m_layout->setSpacing(4);
    m_layout2->setSpacing(4);
    //把画布设置到控件上
    ui->wdg_friend->setLayout(m_layout);
    ui->wdg_ourchat->setLayout(m_layout2);
    //给菜单添加父控件，父控件负责自己的回收
    m_menu=new QMenu(this);

    m_menu->addAction("添加好友");
    m_menu->addAction("删除好友");

    //绑定点击菜单项的信号和槽函数,父类的triggered就是单击信号
    connect(m_menu,SIGNAL(triggered(QAction*)),this,SLOT(slot_deal_pb_Menu_Clicked(QAction*)));
}

myUI::~myUI()
{
    delete ui;
}


void myUI::on_pb_menu_clicked()
{
    //获取鼠标点击坐标
    QPoint p=QCursor::pos();

    //获取菜单的决定高度
    QSize size=m_menu->sizeHint();

    //从鼠标点击位置向上显示菜单项
    m_menu->exec(QPoint(p.x(),p.y()-size.height()));
}

void myUI::slot_deal_pb_Menu_Clicked(QAction* action)
{
    if(action->text()=="添加好友")
    {
        Q_EMIT SIG_addFriend();
    }
    else if(action->text()=="删除好友")
    {
         Q_EMIT SIG_deleteFriend();
    }
}

void myUI::addFriend(userinfo *item)
{
    //直接加控件
    m_layout->addWidget(item);
}



void myUI::setInfo(QString name, QString lable, int iconid)
{
    ui->lb_name->setText(name);
    ui->le_lable->setText(lable);
    ui->pb_icon->setIcon(QIcon(QString(":./tx/%1.png").arg(iconid)));
    this->repaint();
}

void myUI::addOurChat(Chatuserinfo *item)
{
    m_layout2->addWidget(item);
}



void myUI::closeEvent(QCloseEvent *event)
{
    event->accept();
    if(QMessageBox::Yes == QMessageBox::question(this, "提示", "是否确定关闭？"))
    {
        Q_EMIT SIG_closeMyChatDlg();
    }
    else
    {
        event->ignore();
    }
}

