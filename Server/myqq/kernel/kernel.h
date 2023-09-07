<<<<<<< HEAD
#pragma once

#include"../Mediator/TcpMediator.h"
#include"mysql.h"
#include"../config/config.h"
#include<iostream>
#include<map>
#include<list>
#include<signal.h>
#include<sys/wait.h>
using namespace std;
//定义类的函数指针
class CKernel;
typedef void (CKernel::* pFun)(char*, int, long);
//业务类型
typedef struct
{
    pFun Business_Addr;
    void* arg;
}Kernel_bs_t;

typedef struct Kernel_forward_t
{
    int len;
    int clientfd;
    CKernel* pthis;
    char buf[TCP_RECVBUF];
    Kernel_forward_t():len(0),clientfd(-1),pthis(nullptr)
    {
        memset(buf,0,TCP_RECVBUF);
    }
}Kernel_forward_t;

//线程池类型
typedef struct
{
    int Thread_Shutdown;//开关
    int Thread_Max;//线程池最大数量
    int Thread_Min;//线程池最小数量
    int Thread_Alive;//线程池中线程的存活数量
    int Thread_Busy;//线程池中繁忙的线程数量
    int Thread_flag;//缩减数量
    int Front;//队列头
    int Rear;//队列尾
    int Cur;//当前线程数量
    int Max;//队列的最大值
    Kernel_bs_t* Container;//任务队列
    pthread_cond_t Not_Full;
    pthread_cond_t Not_Empty;
    pthread_mutex_t queue_lock;
    pthread_mutex_t var_lock;
    pthread_t mag_tid;//管理者线程
    pthread_t* cus_tids;//消费者线程链表
}Kernel_tp_t;


class CKernel
{
private:
	//中介者类
	INetMediator* m_pMediator;
	//数据库对象
    CMysql sql;
    Kernel_tp_t*tp;
public:
	//函数数组
	pFun m_netProtocolMap[TCP_PROTOCAL_COUNT];
	//保存数据库中用户ID和socket的对应关系
    map<int, int>m_mapIdToSocket;

public:
    CKernel();
	~CKernel();
public:
    static CKernel* GetInstance();
    void EventLoop();
	// 开启服务器
	bool startServer();
	// 关闭服务器
	void closeServer();
	// 处理所有数据，并把数据分派给各个处理函数
	void readyData(char* buf, int nLen,long ISendIP );
	// 初始化协议数组
	void setProtocolMap();
	// 查询好友的信息（包括自己）
	void getUserList(int userID);
	// 根据ID查询信息
	void getUserInfoByID(int ID, STRU_TCP_INFO* info);
	void getUserInfoByID(int ID, STRU_TCP_OUR_CHAT_INFO* info);
	// 处理注册请求
    void dealRegisterRQ(char* buf, int nLen, long ISendIP);
	// 处理登录请求
    void dealLogInRQ(char* buf, int nLen, long ISendIP);
	// 处理聊天请求
    void dealChatRQ(char* buf, int nLen, long ISendIP);
	// 处理添加好友请求
    void dealAddFriendRQ(char* buf, int nLen, long ISendIP);
	// 处理添加好友回复
    void dealAddFriendRS(char* buf, int nLen, long ISendIP);
	// 处理下线请求
    void dealOfflineRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件信息请求
    void dealFileInfoRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件信息响应
    void dealFileInfoRS(char* buf, int nLen, long ISendIP);
	// 处理发送文件块请求
    void dealFileBlockRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件块响应
    void dealFileBlockRS(char* buf, int nLen, long ISendIP);
	// 处理群聊创建请求
    void dealOurChatRQ(char* buf, int nLen, long ISendIP);
	// 得到群聊联系人列表
    void getOurChatList(int ourChatID,int UserID);

	//处理群聊消息的请求
	void dealOurChatTalkRQ(char* buf, int nLen, long ISendIP);

	//md5加密
	static string getMD5(const char* val);
    static int IF_THREAD_ALIVE(pthread_t tid);
    int TP_Create();//线程池创建和初始化数据
    int TP_Destroy();//释放线程池的内存资源
    int TP_Producer(Kernel_bs_t business);//执行一次添加一次任务
    static void* TP_Manager(void *arg);
    static void* TP_Customer(void *arg);
};



=======
#pragma once

#include"../Mediator/TcpMediator.h"
#include"mysql.h"
#include"../config/config.h"
#include<iostream>
#include<map>
#include<list>
#include<signal.h>
#include<sys/wait.h>
using namespace std;
//定义类的函数指针
class CKernel;
typedef void (CKernel::* pFun)(char*, int, long);
//业务类型
typedef struct
{
    pFun Business_Addr;
    void* arg;
}Kernel_bs_t;

typedef struct Kernel_forward_t
{
    int len;
    int clientfd;
    CKernel* pthis;
    char buf[TCP_RECVBUF];
    Kernel_forward_t():len(0),clientfd(-1),pthis(nullptr)
    {
        memset(buf,0,TCP_RECVBUF);
    }
}Kernel_forward_t;

//线程池类型
typedef struct
{
    int Thread_Shutdown;//开关
    int Thread_Max;//线程池最大数量
    int Thread_Min;//线程池最小数量
    int Thread_Alive;//线程池中线程的存活数量
    int Thread_Busy;//线程池中繁忙的线程数量
    int Thread_flag;//缩减数量
    int Front;//队列头
    int Rear;//队列尾
    int Cur;//当前线程数量
    int Max;//队列的最大值
    Kernel_bs_t* Container;//任务队列
    pthread_cond_t Not_Full;
    pthread_cond_t Not_Empty;
    pthread_mutex_t queue_lock;
    pthread_mutex_t var_lock;
    pthread_t mag_tid;//管理者线程
    pthread_t* cus_tids;//消费者线程链表
}Kernel_tp_t;


class CKernel
{
private:
	//中介者类
	INetMediator* m_pMediator;
	//数据库对象
    CMysql sql;
    Kernel_tp_t*tp;
public:
	//函数数组
	pFun m_netProtocolMap[TCP_PROTOCAL_COUNT];
	//保存数据库中用户ID和socket的对应关系
    map<int, int>m_mapIdToSocket;

public:
    CKernel();
	~CKernel();
public:
    static CKernel* GetInstance();
    void EventLoop();
	// 开启服务器
	bool startServer();
	// 关闭服务器
	void closeServer();
	// 处理所有数据，并把数据分派给各个处理函数
	void readyData(char* buf, int nLen,long ISendIP );
	// 初始化协议数组
	void setProtocolMap();
	// 查询好友的信息（包括自己）
	void getUserList(int userID);
	// 根据ID查询信息
	void getUserInfoByID(int ID, STRU_TCP_INFO* info);
	void getUserInfoByID(int ID, STRU_TCP_OUR_CHAT_INFO* info);
	// 处理注册请求
    void dealRegisterRQ(char* buf, int nLen, long ISendIP);
	// 处理登录请求
    void dealLogInRQ(char* buf, int nLen, long ISendIP);
	// 处理聊天请求
    void dealChatRQ(char* buf, int nLen, long ISendIP);
	// 处理添加好友请求
    void dealAddFriendRQ(char* buf, int nLen, long ISendIP);
	// 处理添加好友回复
    void dealAddFriendRS(char* buf, int nLen, long ISendIP);
	// 处理下线请求
    void dealOfflineRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件信息请求
    void dealFileInfoRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件信息响应
    void dealFileInfoRS(char* buf, int nLen, long ISendIP);
	// 处理发送文件块请求
    void dealFileBlockRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件块响应
    void dealFileBlockRS(char* buf, int nLen, long ISendIP);
	// 处理群聊创建请求
    void dealOurChatRQ(char* buf, int nLen, long ISendIP);
	// 得到群聊联系人列表
    void getOurChatList(int ourChatID,int UserID);
    // 处理群聊消息的请求
	void dealOurChatTalkRQ(char* buf, int nLen, long ISendIP);
    // 处理聊天内容的请求
    void dealTalkContentRQ(char* buf, int nLen, long ISendIP);
    // 处理群聊聊天内容的请求
    void dealOurTalkContentRQ(char* buf, int nLen, long ISendIP);
    // 处理音视频请求
    void dealAudioTalkRq(char*buf,int nLen,long ISendIP);
    // 处理音视频回复
    void dealAudioTalkRs(char*buf,int nLen,long ISendIP);
    // 处理音频
    void dealAudioInfoRq(char*buf,int nLen,long ISendIP);
    // 处理视频
    void dealVedioInfoRq(char*buf,int nLen,long ISendIP);
    // 音视频同步发包
	//md5加密
    void GetChatContent(int userid,int friendid,int linkid,int startnum,int endnum,list<string>&res);
	static string getMD5(const char* val);
    static int IF_THREAD_ALIVE(pthread_t tid);
    int TP_Create();//线程池创建和初始化数据
    int TP_Destroy();//释放线程池的内存资源
    int TP_Producer(Kernel_bs_t business);//执行一次添加一次任务
    static void* TP_Manager(void *arg);
    static void* TP_Customer(void *arg);
};



>>>>>>> bbdc256 (version and audio)
