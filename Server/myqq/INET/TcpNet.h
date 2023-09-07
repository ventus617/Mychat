<<<<<<< HEAD
#include"INET.h"
#include<map>
#include<list>
#include<pthread.h>
#include"../config/config.h"
class TcpNet;
typedef void*(*FB)(void*);
//业务类型
typedef struct
{
    FB Business_Addr;
    void* arg;
}bs_t;

typedef struct MySend
{
    int len;
    int sock;
    char buf[TCP_RECVBUF];
    MySend():len(0),sock(-1)
    {
        memset(buf,0,TCP_RECVBUF);
    }
}send_t;

typedef struct
{
    int clientfd;
    TcpNet* pthis;
}forward_t;

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
    bs_t* Container;//任务队列
    pthread_cond_t Not_Full;
    pthread_cond_t Not_Empty;
    pthread_mutex_t queue_lock;
    pthread_mutex_t var_lock;
    pthread_t mag_tid;//管理者线程
    pthread_t* cus_tids;//消费者线程链表
}tp_t;
typedef struct
{
    int Thread_Shutdown;//开关
    int Front;//队列头
    int Rear;//队列尾
    int Cur;//当前线程数量
    int Max;//队列的最大值
    bs_t* Container;//任务队列
    pthread_cond_t Not_Full;
    pthread_cond_t Not_Empty;
    pthread_mutex_t queue_lock;
    pthread_t send_tid;//发送者线程
}send_poll_t;
class TcpNet :public INet
{
public:
	TcpNet(INetMediator* m_p);
	~TcpNet();
public:
	//初始化网络
	 bool InitNet() override;
	//关闭网络
	 void UinitNet() override;
	//发送信息
	 bool SendData(char* buf, int len, long Ip) override;
	//接收信息
	 void AcceptData() override;
     void Eventloop() override;

protected:
    tp_t*tp;
    int m_sock;
    bool m_isStop;
    send_poll_t*send_tp;
    set<int>sockset;
public:

    tp_t* TP_Create();//线程池创建和初始化数据
    send_poll_t* TP_Send_Create();
    int TP_Send_Poll_Create(send_poll_t*send_tp);//创建发送任务队列池
    int TP_Destroy();//释放线程池的内存资源
    int TP_Epoll_Create();//创建监听,进行监听设置
    int TP_Epoll_Listen();//负责持续边缘触发监听(生产者)
    int TP_Producer(bs_t business,tp_t*tp);//执行一次添加一次任务
    int TP_Producer(bs_t business,send_poll_t*send_tp);//执行一次添加一次任务
    static void* TP_Manager(void *arg);
    static void* TP_Customer(void *arg);
    static void* TP_SEND_Customer(void*arg);
    void Accept_business(int serverfd);
//    int IF_THREAD_ALIVE(pthread_t tid);
//    void* Accept_business(void *arg);
//    void* Forward_business(void *arg);
//    void* MySendData(void* arg);

};







=======
#include"INET.h"
#include<map>
#include<list>
#include<pthread.h>
#include"../config/config.h"
class TcpNet;
typedef void*(*FB)(void*);
//业务类型
typedef struct
{
    FB Business_Addr;
    void* arg;
}bs_t;

typedef struct MySend
{
    int len;
    int sock;
    char buf[TCP_RECVBUF];
    MySend():len(0),sock(-1)
    {
        memset(buf,0,TCP_RECVBUF);
    }
}send_t;

typedef struct
{
    int clientfd;
    TcpNet* pthis;
}forward_t;

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
    bs_t* Container;//任务队列
    pthread_cond_t Not_Full;
    pthread_cond_t Not_Empty;
    pthread_mutex_t queue_lock;
    pthread_mutex_t var_lock;
    pthread_t mag_tid;//管理者线程
    pthread_t* cus_tids;//消费者线程链表
}tp_t;
typedef struct
{
    int Thread_Shutdown;//开关
    int Front;//队列头
    int Rear;//队列尾
    int Cur;//当前线程数量
    int Max;//队列的最大值
    bs_t* Container;//任务队列
    pthread_cond_t Not_Full;
    pthread_cond_t Not_Empty;
    pthread_mutex_t queue_lock;
    pthread_t send_tid;//发送者线程
}send_poll_t;
class TcpNet :public INet
{
public:
	TcpNet(INetMediator* m_p);
	~TcpNet();
public:
	//初始化网络
	 bool InitNet() override;
	//关闭网络
	 void UinitNet() override;
	//发送信息
	 bool SendData(char* buf, int len, long Ip) override;
	//接收信息
	 void AcceptData() override;
     void Eventloop() override;

protected:
    tp_t*tp;
    int m_sock;
    bool m_isStop;
    send_poll_t*send_tp;
    set<int>sockset;
public:

    tp_t* TP_Create();//线程池创建和初始化数据
    send_poll_t* TP_Send_Create();
    int TP_Send_Poll_Create(send_poll_t*send_tp);//创建发送任务队列池
    int TP_Destroy();//释放线程池的内存资源
    int TP_Epoll_Create();//创建监听,进行监听设置
    int TP_Epoll_Listen();//负责持续边缘触发监听(生产者)
    int TP_Producer(bs_t business,tp_t*tp);//执行一次添加一次任务
    int TP_Producer(bs_t business,send_poll_t*send_tp);//执行一次添加一次任务
    static void* TP_Manager(void *arg);
    static void* TP_Customer(void *arg);
    static void* TP_SEND_Customer(void*arg);
    void Accept_business(int serverfd);
//    int IF_THREAD_ALIVE(pthread_t tid);
//    void* Accept_business(void *arg);
//    void* Forward_business(void *arg);
//    void* MySendData(void* arg);
    void setNonBlockFd(int fd);

    void setRecvBufSize( int fd);
    void setSendBufSize( int fd);
    void setNoDelay( int fd);

};







>>>>>>> bbdc256 (version and audio)
