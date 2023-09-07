#ifndef AUDIOWRITE_H
#define AUDIOWRITE_H

#include <QObject>
#include"world.h"
class AudioWrite : public QObject
{
    Q_OBJECT
public:
    explicit AudioWrite(QObject *parent = nullptr);
    ~AudioWrite();
signals:
public slots:
    void slot_playAudio(QByteArray bt);
private:
    //SPEEX 相关全局变量
    SpeexBits bits_dec;
    void *Dec_State;
    QAudioOutput*m_audioOut;
    QIODevice* m_buf_out;
    QAudioFormat format;
};

#endif // AUDIOWRITE_H
