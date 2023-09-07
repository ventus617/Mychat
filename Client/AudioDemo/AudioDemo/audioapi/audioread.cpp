#include "audioread.h"


//数据量 40ms 640字节
//1s的数据量 640*25=16000 byte

// speex 窄带模式 8Khz 20ms 采样点160 每一个点是float类型进行编码 操作320字节 变成大端类型来存储
AudioRead::AudioRead(QObject *parent) : QObject(parent)
{
    //speex 初始化
    speex_bits_init(&bits_enc);
    Enc_State = speex_encoder_init(speex_lib_get_mode(SPEEX_MODEID_NB));
    //设置质量为 8(15kbps)
    int tmp = SPEEX_QUALTY;
    speex_encoder_ctl(Enc_State,SPEEX_SET_QUALITY,&tmp);

    //声卡采样 采样率8KHZ 位宽16bit 单声道
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
    m_audio_in=nullptr;
    m_buffer_in=nullptr;
    m_timer=new QTimer;
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_ReadMore()));

    m_audioState=stopped;
}
//当到时后，就读取数据，当640B 之后2个包 抛出

//SPEEK压缩率8.4 从640B到76B
void AudioRead::slot_ReadMore()
{

#ifdef USE_SPEEX
    if (!m_audio_in)
        return;
    QByteArray m_buffer(2048,0);
    qint64 len = m_audio_in->bytesReady();
    if (len < 640)
    {
        return;
    }
    qint64 l = m_buffer_in->read(m_buffer.data(), 640);
    QByteArray frame;
    //speex编码
    char bytes[800] = {0};
    int i = 0;
    float input_frame1[320];
    char buf[800] = {0};
    char* pInData = (char*)m_buffer.data() ;
    memcpy( buf , pInData , 640);
    int nbytes = 0;
    {
        short num = 0;
        for (i = 0;i < 160;i++)
        {
            //转换成大端 再变成float类型
            num = (uint8_t)buf[2 * i] | (((uint8_t)buf[2 * i + 1]) << 8);
            input_frame1[i] = num;
            //num = m_buffer[2 * i] | ((short)(m_buffer[2 * i + 1]) << 8);
            //qDebug() << "float in" << num << input_frame1[i];
        }
        //压缩数据
        speex_bits_reset(&bits_enc);
        speex_encode(Enc_State,input_frame1,&bits_enc);
        nbytes = speex_bits_write(&bits_enc,bytes,800);
        frame.append(bytes,nbytes);
        //大端
        for (i = 0;i < 160;i++)
        {
            num = (uint8_t)buf[2 * i + 320] | (((uint8_t)buf[2 * i + 1 + 320]) << 8);
            input_frame1[i] = num;
        }
        //压缩数据
        speex_bits_reset(&bits_enc);
        speex_encode(Enc_State,input_frame1,&bits_enc);
        nbytes = speex_bits_write(&bits_enc,bytes,800);
        frame.append(bytes,nbytes);
        qDebug() << "nbytes = " << frame.size();
        Q_EMIT SIG_audioFrame (frame);
        return;
    }
//    frame.append(m_buffer.data(),640);//追加到数组后
//    Q_EMIT SIG_audioFrame( frame );//通过数组抛出
#else
    if (!m_audio_in)
    return;
    QByteArray m_buffer(2048,0);
    qint64 len = m_audio_in->bytesReady();
    if (len < 640)
    {
        return;
    }
    qint64 l = m_buffer_in->read(m_buffer.data(), 640);
    QByteArray frame;
    frame.append(m_buffer.data(),640);//追加到数组后
    Q_EMIT SIG_audioFrame( frame );//通过数组抛出
#endif
}

//当开始的时候，就创建音频输入对象来获取数据，此时状态切换playing
void AudioRead::start()
{
    if(m_audioState==stopped||m_audioState==pausing)
    {
        m_audio_in=new QAudioInput(format,this);
        //返回采集地址给成员
        m_buffer_in=m_audio_in->start();//开始声音采集

        m_timer->start(25);
        m_audioState=playing;
    }
}

//当暂停的时候，就回收掉音频输入对象，此时状态切换pausing
void AudioRead::pause()
{
    if(m_audioState==playing)
    {
        m_timer->stop();
        if(m_audio_in)
        {
            m_audio_in->stop();
            delete m_audio_in;
        }
        m_audioState=pausing;
    }
}
