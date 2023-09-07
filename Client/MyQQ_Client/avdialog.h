#ifndef AVDIALOG_H
#define AVDIALOG_H

#include <QDialog>
#include"usershow.h"
#include "customwidget.h"
namespace Ui {
class avdialog;
}

class avdialog : public CustomMoveDialog
{
    Q_OBJECT

public:
    explicit avdialog(QWidget *parent = nullptr);
    ~avdialog();
    void InitAvcall(int id,int userid);
    QMap<int,UserShow*>m_mapIdToUserShow;

private slots:
    void on_qc_audio_clicked();

    void on_pb_small_clicked();

    void on_pb_max_clicked();

    void on_pb_close_clicked();

    void on_qc_video_clicked();
signals:
    void SIG_audio_play();

    void SIG_audio_pause();

    void SIG_video_play(int id);

    void SIG_video_pause();

    void SIG_close();

private:
    Ui::avdialog *ui;
    UserShow* m_user[2];
    int m_id;
};

#endif // AVDIALOG_H
