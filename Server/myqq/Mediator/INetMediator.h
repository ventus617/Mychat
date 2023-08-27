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
using namespace std;
//中介者模式的中介者
class INet;//针对两者互相联系，触发重复包含问题，就直接使用声明即可，不需要使用头文件
class INetMediator
{
public:
    INetMediator();
    virtual ~INetMediator();
public:
	//初始化网络
	virtual bool OpenNet() = 0;
	//关闭网络
	virtual void CloseNet() = 0;
	//发送数据
	virtual bool SendData(char* buf, int nlen, long Ip) = 0;
	//接收数据
	virtual void AcceptData(char* buf, int nlen, long Ip) = 0;
    virtual void Eventloop()=0;
protected:
	INet* m_pNet;
};
