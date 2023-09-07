#include"UdpMediator.h"
#include"UdpNet.h"
//构造
UdpMediator::UdpMediator()
{
	m_pNet = new UdpNet(this);//获得底层服务的对象指针，每个底层服务均要知道中介者，因此中介者来生成底层对象，并传this指针
}
//析构
UdpMediator::~UdpMediator()
{
	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = nullptr;
	}
}
//初始化网络
bool UdpMediator::OpenNet()
{
	return m_pNet->InitNet();
}
//关闭网络
void UdpMediator::CloseNet()
{
	m_pNet->UinitNet();
}
//发送消息
bool UdpMediator::SendData(char* buf, int len, long Ip)
{
	return m_pNet->SendData(buf, len, Ip);
}
//接收消息
void UdpMediator::AcceptData(char* buf, int len, long Ip)
{
	cout << buf << endl;
}