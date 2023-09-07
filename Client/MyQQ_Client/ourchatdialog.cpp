#include "ourchatdialog.h"
#include "ui_ourchatdialog.h"
#include <QTime>
#include <QMessageBox>
#include <QTextBrowser>
Ourchatdialog::Ourchatdialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ourchatdialog),m_num(0)
{
    ui->setupUi(this);
    setWindowTitle("聊天窗口");
    //new 一个垂直布局的画布
    m_layout=new QVBoxLayout;
    //设置上下左右距离外边框的间距
    m_layout->setContentsMargins(0,0,0,0);
    //设置画布上每个控件的距离
    m_layout->setSpacing(4);
    //把画布设置到控件上
    ui->our_wdg->setLayout(m_layout);
}

Ourchatdialog::~Ourchatdialog()
{
    delete ui;
}

void Ourchatdialog::addMember(ourchatuserinfo* item)
{
    m_layout->addWidget(item);
}

void Ourchatdialog::getMyId(int id)
{
    m_id=id;
}
void Ourchatdialog::set_content(QString content,QString m_name,QString time)
{
    //将接收的聊天内容设置在窗口
    ui->textBrowser->append(QString("[%1]:%2").arg(m_name).arg(time));
    ui->textBrowser->append(content);
}

void Ourchatdialog::set_Mycontent(QString content, QString time, QString name, QString m_name)
{
    content=content.replace(QRegExp("\\\""),"\"");
    content=content.replace(QRegExp("\\'"),"\'");
    ++m_num;
    //将接收的聊天内容设置在窗口
    if(content.isEmpty())
        return;
    ui->textBrowser->moveCursor(QTextCursor::Start);
    if(!name.isEmpty())
    {
        ui->textBrowser->insertPlainText(QString("[%1]:%2\n").arg(name).arg(time));
    }
    else
        ui->textBrowser->insertPlainText(QString("[我]:%1\n").arg(time));
        //ui->textBrowser->insertPlainText(QString("[%1]:%2\n").arg(m_name).arg(time));
//    ui->textBrowser->insertPlainText(QString("[%1]\n").arg(content));
    ui->textBrowser->insertHtml(content);
    ui->textBrowser->insertPlainText(QString("\n"));
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void Ourchatdialog::on_pb_commit_clicked()
{
    QString te_content=ui->textEdit->toPlainText();
    if(te_content.isEmpty()||te_content.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","输入非法");
        return;
    }
    te_content=ui->textEdit->toHtml();
    ui->textEdit->clear();

    QString time=QDate::currentDate().toString("MM-dd");
    time+=QTime::currentTime().toString(" hh:mm:ss");
    ui->textBrowser->append(QString("[我]:%1").arg(time));
    ui->textBrowser->append(te_content);
    te_content=te_content.replace(QRegExp("\""),"\\\"");
    te_content=te_content.replace(QRegExp("\'"),"\\'");
    Q_EMIT SIG_Our_SendMsg(m_id,te_content,time);
}


void Ourchatdialog::on_pb_getmore_clicked()
{
    int startnum=m_num;
    int endnum=m_num+TCP_MORE_CHAT;
    Q_EMIT SIG_Get_MoreChat(startnum,endnum,m_id);
}

