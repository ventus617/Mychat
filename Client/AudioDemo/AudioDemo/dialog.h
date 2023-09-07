#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"audiowrite.h"
#include"audioread.h"
#include <QMap>
#include"videoread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pb_pause_clicked();

    void on_pb_start_clicked();

    void on_pb_video_start_clicked();

    void on_pb_video_pause_clicked();
    void slot_sendVideoFrame(QImage img);

private:
    Ui::Dialog *ui;
    AudioRead * m_read;
    AudioWrite* m_write;
    VideoRead* m_video;
    QMap<int,int>test;
};
#endif // DIALOG_H
