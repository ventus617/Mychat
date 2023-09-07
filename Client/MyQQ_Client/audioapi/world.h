#ifndef WORLD_H
#define WORLD_H
#include<QMessageBox>
#include<QAudioInput>
#include<QAudioOutput>
#include<QDebug>
#include<QIODevice>
#include<stdlib.h>
#include<QTimer>
#include"speex/include/speex.h"
#define SPEEX_QUALTY (8)

enum ENUM_PLAY_STATE{stopped,playing,pausing};

#define USE_SPEEX (1)
#endif // WORLD_H
