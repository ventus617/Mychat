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
//��ʼ������
bool TcpMediator::OpenNet()
{
	if (!m_pNet->InitNet())
	{
		cout << "TcpMediator::OpenNet() error" << endl;
		return false;
	}
	return true;
}
//�ر�����
void TcpMediator::CloseNet()
{
	m_pNet->UinitNet();
}
//��������
bool TcpMediator::SendData(char*buf,int len,long Ip)
{
	if (!m_pNet->SendData(buf, len, Ip))
	{
		cout << "TcpMediator::SendData error" << endl;
		return false;
	}
	return true;
}
//��������
void TcpMediator::AcceptData(char* buf, int len, long Ip)
{
	CKernel::pKernel->readyData(buf, len, Ip);
}