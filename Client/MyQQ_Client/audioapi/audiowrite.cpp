#include "audiowrite.h"

AudioWrite::AudioWrite(QObject *parent) : QObject(parent)
{
    //声卡采样 采样率8KHZ 位宽16bit 单声道
    //speex 初始化
    speex_bits_init(&bits_dec);
    Dec_State = speex_decoder_init(speex_lib_get_mode(SPEEX_MODEID_NB));

    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");//编码格式
    format.setByteOrder(QAudioFormat::LittleEndian);//小端存储
    format.setSampleType(QAudioFormat::UnSignedInt);//无符号整型
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();//默认打开设备
    if (!info.isFormatSupported(format)) {
    QMessageBox::information(NULL , "提示", "打开音频设备失败");
    format = info.nearestFormat(format);
    }
    m_audioOut=new QAudioOutput(format,this);
    //向buffer里面存数据,就会触发播放声音
    m_buf_out=m_audioOut->start();

}

AudioWrite::~AudioWrite()
{

}

void AudioWrite::slot_playAudio(QByteArray ba)
{
#ifdef USE_SPEEX
    char bytes[800] = {0};
    int i = 0;
    float output_frame1[320] = {0};
    char buf[800] = {0};
    memcpy(bytes,ba.data(),ba.length() / 2);
    //解压缩数据 106 62
    //speex_bits_reset(&bits_dec);
    speex_bits_read_from(&bits_dec,bytes,ba.length() / 2);
    int error = speex_decode(Dec_State,&bits_dec,output_frame1);
    //将解压后数据转换为声卡识别格式
    //第一次的320字节的操作
    //大端->小端 我们底层获取声音的时候是小端模式，SPEEK支持大端的float类型的模式
    short num = 0;
    for (i = 0;i < 160;i++)
    {
        num = output_frame1[i];
        buf[2 * i] = num;
        buf[2 * i + 1] = num >> 8;
        //qDebug() << "float out" << num << output_frame1[i];
    }
    memcpy(bytes,ba.data() + ba.length() / 2,ba.length() / 2);
    //解压缩数据
    //speex_bits_reset(&bits_dec);
    speex_bits_read_from(&bits_dec,bytes,ba.length() / 2);
    error = speex_decode(Dec_State,&bits_dec,output_frame1);
    //将解压后数据转换为声卡识别格式
    //第二次的320字节的操作
    //大端->小端
    for (i = 0;i < 160;i++)
    {
        num = output_frame1[i];
        buf[2 * i + 320] = num;
        buf[2 * i + 1 + 320] = num >> 8;
    }
    m_buf_out->write(buf,640);
    return;
#else
    if(bt.size()<640) return ;
    m_buf_out->write(bt.data(),640);
#endif
}
