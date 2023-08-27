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
private:
    myUI* m_pMyUI;
    INetMediator* m_pMediator;
    logindialog* m_pMyLogInDlg;
    //保存自己的id和姓名
    int m_Id;
    QString m_name;

    // 保存用户ID和对应聊天窗口
    QMap<int, chatdialog*> m_mapIDToChatdlg;

    //保存用户id和好友信息窗口
    QMap<int,userinfo*> m_mapIdToUserinfo;

    //保存群聊id和群聊窗口
    QMap<int,Ourchatdialog*> m_mapIDToOurChatdlg;
    //保存ourchatselect端口的内容
    ourchatselect* m_select;

    //保存select界面的ui
    QMap<int,friendselect*> m_mapIdTOOurSelect;

    //保存群聊的窗口和群聊的id
    QMap<int,Chatuserinfo*> m_mapIdToChatUserinfo;
    //保存每个文件的大小
    QMap<FILE*,int> m_mapFileToFileSize;
    //保存每个窗口对应的发送文件指针
    QMap<chatdialog*,FILE*> m_mapChatdlgToFile;
    //保存每个窗口对应的接收文件指针
    QMap<chatdialog*,FILE*> m_mapChatdlgToAcceptFile;
    //保存每个窗口对应的文件偏移量
    QMap<chatdialog*,int> m_mapChatdlgToOffset;
    //保存文件的默认路径
    QString selectDir;
    //保存文件名
    QMap<int,QString> m_mapIdToFileName;
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
    void slot_sendMsg(int ID, QString content);
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
    void slot_Our_sendMsg(int ID, QString content);
    // 处理发送文件
    void slot_send_file (int ID,QString filename);
    // 暂停文件发送
    void slot_pause_file (int ID);

    
};

#endif // CKERNEL_H
