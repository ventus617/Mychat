#ifndef AUDIOREAD_H
#define AUDIOREAD_H

#include <QObject>
#include"world.h"
class AudioRead : public QObject
{
    Q_OBJECT
public:
    explicit AudioRead(QObject *parent = nullptr);
    ~ AudioRead();
signals:
    void SIG_audioFrame(QByteArray bt);//字节数组 char*
public:
    void start();
    void pause();
    QAudioInput *m_audio_in;//采集声卡的音频输入
    QIODevice * m_buffer_in;//音频输入的缓冲区
    QTimer * m_timer;
    QAudioFormat format;
    int m_audioState;

    //SPEEX 相关变量
    SpeexBits bits_enc;
    void *Enc_State;
public slots:
    void slot_ReadMore();//定时超时,从缓冲区读取音频数据

};

#endif // AUDIOREAD_H
