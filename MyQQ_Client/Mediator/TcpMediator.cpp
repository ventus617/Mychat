#include"TcpMediator.h"
#include"../INET/TcpClient.h"

TcpClientMediator::TcpClientMediator()
{
    m_pNet = new TcpClient(this);
}

TcpClientMediator::~TcpClientMediator()
{
	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = nullptr;
	}
}
//初始化网络
bool TcpClientMediator::OpenNet()
{
	if (!m_pNet->InitNet())
	{
		cout << "TcpMediator::OpenNet() error" << endl;
		return false;
	}
	return true;
}
//关闭网络
void TcpClientMediator::CloseNet()
{
	m_pNet->UinitNet();
}
//发送数据
bool TcpClientMediator::SendData(char*buf,int len,long Ip)
{
	if (!m_pNet->SendData(buf, len, Ip))
	{
		cout << "TcpMediator::SendData error" << endl;
		return false;
	}
	return true;
}
//接收数据
void TcpClientMediator::AcceptData(char* buf, int len, long Ip)
{
    Q_EMIT SIG_readData(buf,len,Ip);
}
