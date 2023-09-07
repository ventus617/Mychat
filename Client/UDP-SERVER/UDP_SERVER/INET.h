#pragma once
#include<iostream>
#include<winsock.h>
using namespace std;
#pragma comment(lib,"Ws2_32.lib")

class INetMediator;
//中介者模式的用户A，作为底层网络的父类
class INet//
{
public:
	INet(){}
	virtual ~INet(){}//因为是父类，作为接口类，因此虚析构
public:
	//初始化网络
	virtual bool InitNet() = 0;
	//关闭网络
	virtual void UinitNet() = 0;
	//发送信息
	virtual bool SendData(char* buf, int len, long Ip) = 0;
protected:
	//接收信息
	virtual void AcceptData() = 0;
	INetMediator* m_pMediator;
};