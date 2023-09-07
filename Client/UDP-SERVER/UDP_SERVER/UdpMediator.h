#pragma once
#include"INetMediator.h"
#include"config.h"
class UdpMediator :public INetMediator
{
public:
	UdpMediator();
	~UdpMediator()override;
public:
	//初始化网络
	bool OpenNet()override;
	//关闭网络
	void CloseNet()override;
	//发送数据
	bool SendData(char* buf, int nlen, long Ip)override;
	//接收数据,底层收到的数据获得的ip等内容作为传参的方式传给中介者
	void AcceptData(char* buf, int nlen, long Ip)override;
};