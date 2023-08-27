#pragma once
#include<iostream>
#include<winsock.h>
#include<QObject>
using namespace std;
//中介者模式的中介者
class INet;//针对两者互相联系，触发重复包含问题，就直接使用声明即可，不需要使用头文件
class INetMediator:public QObject
{
    Q_OBJECT
public:
	INetMediator(){}
	virtual ~INetMediator(){}
public:
	//初始化网络
	virtual bool OpenNet() = 0;
	//关闭网络
	virtual void CloseNet() = 0;
	//发送数据
	virtual bool SendData(char* buf, int nlen, long Ip) = 0;
	//接收数据
	virtual void AcceptData(char* buf, int nlen, long Ip) = 0;
protected:
	INet* m_pNet;
};
