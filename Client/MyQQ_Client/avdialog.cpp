#include "avdialog.h"
#include "ui_avdialog.h"
#include<QDebug>
avdialog::avdialog(QWidget *parent) :
    CustomMoveDialog(parent),
    ui(new Ui::avdialog)
{
    ui->setupUi(this);
//    m_user[0]=new UserShow;
//    m_user[1]=new UserShow;
    m_user[0] = ui->wd_big ;
    m_user[1] = ui->wd_small ;
}

avdialog::~avdialog()
{
    delete ui;
}

void avdialog::InitAvcall(int id, int userid)
{
    m_id=id;
    m_user[0]->setinfo(id);
    m_user[1]->setinfo(userid);
    m_mapIdToUserShow[id]=m_user[0];
    m_mapIdToUserShow[userid]=m_user[1];
    ui->lb_title->setText(QString("通话中"));
}

//就是变成点击一下就开始，点击一下就停止
//如果是选中的,就停止然后设置为未选中的,如果是未选中的就设置成选中了
void avdialog::on_qc_audio_clicked()
{
    if(ui->qc_audio->isChecked())
    {
        //ui->qc_audio->setChecked(true);
        Q_EMIT SIG_audio_play();
    }
    else
    {
        //ui->qc_audio->setChecked(false);
        Q_EMIT SIG_audio_pause();
    }
}

void avdialog::on_pb_small_clicked()
{
    this->slot_showMin();
}


void avdialog::on_pb_max_clicked()
{
    this->slot_showMax();
}


void avdialog::on_pb_close_clicked()
{
    ui->qc_audio->setChecked(false);
    ui->qc_video->setChecked(false);
    this->hide();
    Q_EMIT SIG_close();
}


void avdialog::on_qc_video_clicked()
{
    if(ui->qc_video->isChecked())
    {
        Q_EMIT SIG_video_play(m_id);
    }
    else
    {
        Q_EMIT SIG_video_pause();
    }
}

