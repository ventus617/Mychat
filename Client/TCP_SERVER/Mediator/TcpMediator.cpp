#include"TcpMediator.h"
#include"../INET/TcpNet.h"
#include"../kernel/kernel.h"

TcpMediator::TcpMediator()
{
	m_pNet = new TcpNet(this);
}

TcpMediator::~TcpMediator()
{
	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = nullptr;
	}
}
//初始化网络
bool TcpMediator::OpenNet()
{
	if (!m_pNet->InitNet())
	{
		cout << "TcpMediator::OpenNet() error" << endl;
		return false;
	}
	return true;
}
//关闭网络
void TcpMediator::CloseNet()
{
	m_pNet->UinitNet();
}
//发送数据
bool TcpMediator::SendData(char*buf,int len,long Ip)
{
	if (!m_pNet->SendData(buf, len, Ip))
	{
		cout << "TcpMediator::SendData error" << endl;
		return false;
	}
	return true;
}
//接收数据
void TcpMediator::AcceptData(char* buf, int len, long Ip)
{
	CKernel::pKernel->readyData(buf, len, Ip);
}