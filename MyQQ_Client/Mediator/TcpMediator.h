#pragma once
#include"INetMediator.h"

class TcpClientMediator :public INetMediator
{
    Q_OBJECT
public:
    TcpClientMediator();
    ~TcpClientMediator();
public:
	//初始化网络
	 bool OpenNet() override;
	//关闭网络
	 void CloseNet() override;
	//发送数据
	 bool SendData(char* buf, int nlen, long Ip) override;
	//接收数据
	 void AcceptData(char* buf, int nlen, long Ip) override;

signals:
     //发送数据给kernel
     void SIG_readData(char*buf,int nlen,long Ip);
};
