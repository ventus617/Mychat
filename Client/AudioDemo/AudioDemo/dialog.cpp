#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_read=new AudioRead;
    m_write=new AudioWrite;
    connect(m_read,SIGNAL( SIG_audioFrame(QByteArray)),m_write,SLOT( slot_playAudio(QByteArray)));
    m_video=new VideoRead;
    connect(m_video,SIGNAL( SIG_sendVideoFrame(QImage)),this,SLOT(slot_sendVideoFrame(QImage)));

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pb_pause_clicked()
{
    test[0]=1;
    test[1]=2;
    qDebug()<<test[0];
    m_read->pause();
}


void Dialog::on_pb_start_clicked()
{
    m_read->start();
}


void Dialog::on_pb_video_start_clicked()
{
    m_video->slot_openVideo();
}


void Dialog::on_pb_video_pause_clicked()
{
    m_video->slot_closeVideo();
}

void Dialog::slot_sendVideoFrame(QImage img)
{
    QPixmap pix=QPixmap::fromImage(img);
    ui->lb_show->setPixmap(pix);
    ui->lb_show->update();
}

