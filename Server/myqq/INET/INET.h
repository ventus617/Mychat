<<<<<<< HEAD
#pragma once
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<sys/types.h>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<map>
#include<list>
#include<pthread.h>
#include<errno.h>
#include<time.h>
#include<sys/epoll.h>
#include<signal.h>
#include<sys/wait.h>
#include<set>
#include<netinet/tcp.h>


using namespace std;

class INetMediator;
//中介者模式的用户A，作为底层网络的父类
class INet//
{
public:
    INet();
    virtual ~INet();//因为是父类，作为接口类，因此虚析构
public:
	//初始化网络
	virtual bool InitNet() = 0;
	//关闭网络
	virtual void UinitNet() = 0;
	//发送信息
	virtual bool SendData(char* buf, int len, long Ip) = 0;
    virtual void Eventloop()=0;
    INetMediator* m_pMediator;
protected:
	//接收信息
	virtual void AcceptData() = 0;

};
=======
#pragma once
#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<sys/types.h>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<map>
#include<list>
#include<pthread.h>
#include<errno.h>
#include<time.h>
#include<sys/epoll.h>
#include<signal.h>
#include<sys/wait.h>
#include<set>
#include<netinet/tcp.h>


using namespace std;

class INetMediator;
//中介者模式的用户A，作为底层网络的父类
class INet//
{
public:
    INet();
    virtual ~INet();//因为是父类，作为接口类，因此虚析构
public:
	//初始化网络
	virtual bool InitNet() = 0;
	//关闭网络
	virtual void UinitNet() = 0;
	//发送信息
	virtual bool SendData(char* buf, int len, long Ip) = 0;
    virtual void Eventloop()=0;
    INetMediator* m_pMediator;
protected:
	//接收信息
	virtual void AcceptData() = 0;

};
>>>>>>> bbdc256 (version and audio)
