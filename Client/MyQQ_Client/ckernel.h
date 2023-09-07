#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include"TcpMediator.h"
#include<QMap>
#include<QList>
#include<QSet>
#include"config.h"
#include"myui.h"
#include"chatdialog.h"
#include"logindialog.h"
#include"userinfo.h"
#include<QDebug>
#include"md5.h"
#include"friendselect.h"
#include"ourchatselect.h"
#include "ourchatdialog.h"
#include"ourchatuserinfo.h"
#include "chatuserinfo.h"
#include<QFileDialog>
#include "audioread.h"
#include "audiowrite.h"
#include <map>
#include"videoread.h"
class ckernel;
typedef void (ckernel::*pfun)(char*,int,long);
class ckernel : public QObject
{
    Q_OBJECT
public:
    explicit ckernel(QObject *parent = nullptr);
    ~ckernel();
public:
    //处理函数的数组
    pfun m_netProtocalMap[TCP_PROTOCAL_COUNT];
public:
    myUI* m_pMyUI;
    INetMediator* m_pMediator;
    //单个音频 单个输入
    AudioRead * m_pAudioRead;
    AudioWrite * m_pAudioWrite;

    int m_isAudio;
    int m_audioFriendid;
    //视频采集
    int m_videochatid;
    VideoRead* m_pVideoRead;
    logindialog* m_pMyLogInDlg;
    //保存自己的id和姓名
    int m_Id;
    QString m_name;

    //保存用户id和好友信息窗口
    map<int,userinfo*> m_mapIdToUserinfo;

    // 保存用户ID和对应聊天窗口
    map<int, chatdialog*> m_mapIDToChatdlg;

    //保存群聊id和群聊窗口
    map<int,Ourchatdialog*> m_mapIDToOurChatdlg;

    //保存ourchatselect端口的内容
    ourchatselect* m_select;

    //保存select界面的ui
    map<int,friendselect*> m_mapIdTOOurSelect;

    //保存群聊的窗口和群聊的id
    map<int,Chatuserinfo*> m_mapIdToChatUserinfo;

    //保存每个文件的大小
    map<FILE*,int> m_mapFileToFileSize;
    //保存每个窗口对应的发送文件指针
    map<chatdialog*,FILE*> m_mapChatdlgToFile;
    //保存每个窗口对应的接收文件指针
    map<chatdialog*,FILE*> m_mapChatdlgToAcceptFile;
    //保存每个窗口对应的文件偏移量
    map<chatdialog*,int> m_mapChatdlgToOffset;
    //保存文件的默认路径
    QString selectDir;
    //保存文件名
    map<int,QString> m_mapIdToFileName;


public:
    // 初始化协议数组
    void setProtocolMap();
    // 处理注册回复
    void dealRegisterRS(char* buf, int nLen,long Ip);
    // 处理登录回复
    void dealLogInRS(char* buf, int nLen,long Ip);
    // 处理好友信息
    void dealFriendInfo(char* buf, int nLen,long Ip);
    // 处理聊天回复
    void dealChatRS(char* buf, int nLen,long Ip);
    // 处理聊天请求
    void dealChatRQ(char* buf, int nLen,long Ip);
    // 处理添加好友请求
    void dealAddRQ(char* buf, int nLen,long Ip);
    // 处理添加好友回复
    void dealAddRS(char* buf, int nLen,long Ip);
    // 处理下线请求
    void dealOfflineRQ(char* buf, int nLen,long Ip);
    // 处理添加群聊回复
    void dealOurChatRS(char* buf, int nLen,long Ip);
    // 处理群聊好友信息
    void dealOurChatFriendInfo(char* buf, int nLen,long Ip);
    // 处理群聊消息
    void dealOurChatTalk(char* buf, int nLen,long Ip);
    // 处理发送文件信息请求
    void dealFileInfoRQ(char* buf, int nLen, long IP);
    // 处理发送文件信息响应
    void dealFileInfoRS(char* buf, int nLen, long IP);
    // 处理发送文件块请求
    void dealFileBlockRQ(char* buf, int nLen, long IP);
    // 处理发送文件块响应
    void dealFileBlockRS(char* buf, int nLen, long IP);
    // 处理聊天内容请求
    void dealChatContent(char* buf, int nLen, long IP);
    // 处理群聊天内容请求
    void dealOurChatContent(char* buf, int nLen, long IP);
    // 处理音视频请求
    void dealTalkRq(char*buf,int nLen,long Ip);
    // 处理音视频回复
    void dealTalkRs (char*buf,int nLen,long Ip);
    // 处理音频帧
    void dealAudioFrameRq(char*buf,int nLen,long Ip);
    void dealAudioFrameRs(char*buf,int nLen,long Ip);
    // 处理视频帧
    void dealVedioFrameRq(char*buf,int nLen,long Ip);
    void dealVedioFrameRs(char*buf,int nLen,long Ip);

    // QT使用UTF-8编码格式，VS和MySQL使用gb2312编码格式
    // QString就是UTF-8编码格式，char*可以装gb2312编码格式的字符串
    // UTF-8转gb2312
    void utf8ToGb2312(QString utf8, char* gb2312, int len);
    // gb2312转UTF-8
    QString gb2312ToUtf8(char* gb2312);
    //MD5加密
   static string getMD5(const QString val);
   //获取文件名字
   void GetFileName(char* filename, QString path);
signals:
   void SIG_SendSelect(ourchatselect* m_select);
    
public slots:
    // 接收所有数据，并分派给对应的处理函数
    void slot_readyData( char* buf, int nLen,long IP);
    // 处理注册界面的用户输入内容
    void slot_registerCommit(QString tel, QString name, QString password);
    // 处理登录界面的用户输入内容
    void slot_LogInCommit(QString tel, QString password);
    // 处理用户要发送的聊天内容给客户端
    void slot_sendMsg(int ID, QString content,QString time);
    // 处理显示聊天窗口
    void slot_showChatDlg(int ID);
    // 处理显示群聊聊天窗口
    void slot_showOurChatDlg(int ID);
    // 给kernel发信号，添加好友
    void slot_addFriend();
    // 处理关闭登录窗口的信号
    void slot_closeLogInDlg();
    // 处理关闭好友列表窗口的信号
    void slot_closeMyUIDlg();
    // 删除好友
    void slot_deleteFriend();
    // 打开选择好友窗口
    void slot_ShowSelect();
    // 选中好友
    void slot_selectFriend(QSet<int>* set);
    // 发送群聊消息
    void slot_Our_sendMsg(int ID, QString content,QString time);
    // 处理发送文件
    void slot_send_file (int ID,QString filename);
    // 暂停文件发送
    void slot_pause_file (int ID);
    // 申请更多聊天内容
    void slot_getmore_chat(int startnum,int endnum,int friendid);
    // 申请更多的群聊的聊天内容;
    void slot_getmore_ourchat(int startnum,int endnum,int linkid);
    // 处理音视频聊天请求
    void slot_talk_rq(int friendid);
    // 处理关闭音视频界面的信号
    void slot_close_talk();
    // 处理语言聊天
    void slot_audio_play();
    void slot_audio_pause();
    void slot_video_play(int id);
    void slot_video_pause();
    // 刷新图片显示
    void slot_refreshvideo(int id,int m_id,QImage& img);


    //发送视频帧
    void slot_videoFrame(QImage img);
    // 发送音频帧
    void slot_audioFrame(QByteArray ba);

};

#endif // CKERNEL_H
