#include "chatdialog.h"
#include "ui_chatdialog.h"
#include<QMessageBox>
#include<QTime>
#include<QDebug>
#include <QFileDialog>
#include"config.h"
chatdialog::chatdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chatdialog)
{
    ui->setupUi(this);
    m_num=0;
    m_call=new avdialog;

}

chatdialog::~chatdialog()
{
    delete m_call;
    m_call=nullptr;
    delete ui;
}

void chatdialog::on_pb_file_clicked()
{
    qDebug()<<__func__;
    // 1、获取文件名
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "/", "全部文件 (*.*);;文本 (*.txt)");
    qDebug()<<fileName;
    // 2、通过信号把文件名发给kernel
    Q_EMIT SIG_SendFile(m_id, fileName);
}

//设置窗口属性，通过kernel初始化的时候设置
void chatdialog::setWindowInfo(QString name, int ID,int Userid)
{
    // 保存好友的ID和好友的姓名name
    m_id = ID;
    m_name = name;
    m_userid=Userid;
    m_call->InitAvcall(m_id,m_userid);
    // 设置窗口标题
    setWindowTitle(QString("与 %1 的聊天窗口").arg(m_name));
}

void chatdialog::IfOffline()
{
    QString time=QTime::currentTime().toString("hh:mm:ss");
    ui->tb_chat->append(QString("[%1]:[%2]").arg(m_name).arg(time));
    ui->tb_chat->append(QString("[自动回复]已读不回,谢谢惠顾"));
}

void chatdialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->hide();
}
void chatdialog::on_pb_talk_clicked()
{
    Q_EMIT SIG_TALK_RQ(m_id);
    //m_call->showNormal();
}


void chatdialog::on_pb_ourchat_clicked()
{
     qDebug()<<__func__;
    Q_EMIT SIG_getSelect();
}


void chatdialog::on_pb_commit_clicked()
{
    QString te_content=ui->te_chat->toPlainText();
    if(te_content.isEmpty()||te_content.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","输入非法");
        return;
    }
    te_content=ui->te_chat->toHtml();
    ui->te_chat->clear();
    QString time=QDate::currentDate().toString("MM-dd");
    time+=QTime::currentTime().toString(" hh:mm:ss");
    ui->tb_chat->append(QString("[我]:%1").arg(time));
    ui->tb_chat->append(te_content);
    te_content=te_content.replace(QRegExp("\""),"\\\"");
    te_content=te_content.replace(QRegExp("\'"),"\\'");
    Q_EMIT SIG_SendMsg(m_id,te_content,time);

}


void chatdialog::set_content(QString content,QString time)
{
    //将接收的聊天内容设置在窗口
    ui->tb_chat->append(QString("[%1]:%2").arg(m_name).arg(time));
    ui->tb_chat->append(content);
}

void chatdialog::set_Mycontent(QString content, QString time, int id)
{
    ++m_num;
    content=content.replace(QRegExp("\\\""),"\"");
    content=content.replace(QRegExp("\\'"),"\'");
    //将接收的聊天内容设置在窗口
    if(content.isEmpty())
        return;
    ui->tb_chat->moveCursor(QTextCursor::Start);
    if(id==m_id)
        ui->tb_chat->insertPlainText(QString("[%1]:%2\n").arg(m_name).arg(time));
    else
        ui->tb_chat->insertPlainText(QString("[我]:%1\n").arg(time));
        //ui->tb_chat->insertPlainText(QString("[%1]:%2\n").arg(m_name).arg(time));
    // ui->tb_chat->insertPlainText(QString("[%1]\n").arg(content));
    ui->tb_chat->insertHtml(content);
    ui->tb_chat->insertPlainText(QString("\n"));
    ui->tb_chat->moveCursor(QTextCursor::End);

}


void chatdialog::on_pb_file_pause_clicked()
{
    Q_EMIT SIG_pauseFile(m_id);
}


void chatdialog::on_pb_morechat_clicked()
{
    int startnum=m_num;
    int endnum=startnum+TCP_MORE_CHAT;
    Q_EMIT SIG_GetMoreChat(startnum,endnum,m_id);
}

