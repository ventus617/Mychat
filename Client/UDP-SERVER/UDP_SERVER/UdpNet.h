#pragma once
#include"INET.h"
#include"config.h"
#include<process.h>
#include<queue>
class UdpNet :public INet
{
public:
	UdpNet(INetMediator* pMediator);//中介者模式，需要一个中介者,它的创建由中介者产生，
	//如果说都通过new的方式来获取，首先会发生循环构造，栈溢出(A的构造需要先构造B，B的构造又需要构造A，交叉构造)
	//其次，不适用，如果来一个底层就创建一个新的中介者，那么中介者就是一个对象匹配一个对象的情况了，而不是一个类匹配多个类，不能实现一个中介者面对多个底层进行处理的情况了
	~UdpNet()override;
public:
	bool InitNet()override;
	//关闭网络
	 void UinitNet()override;
	//发送信息
	 bool SendData(char* buf, int len, long Ip)override;
protected:
	//接收数据的线程 static 在未创建对象的时候，就需要使用静态成员函数
	static unsigned int _stdcall RecvThread(void* lpVoid);
	//接收数据 
	void AcceptData()override;
	//关闭服务器
	void SetStop();
	SOCKET m_sock;//自己的套接字
	HANDLE m_handle;//线程句柄
	bool m_stop;//服务器停止工作

};