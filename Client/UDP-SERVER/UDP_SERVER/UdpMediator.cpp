#include"UdpMediator.h"
#include"UdpNet.h"
//����
UdpMediator::UdpMediator()
{
	m_pNet = new UdpNet(this);//��õײ����Ķ���ָ�룬ÿ���ײ�����Ҫ֪���н��ߣ�����н��������ɵײ���󣬲���thisָ��
}
//����
UdpMediator::~UdpMediator()
{
	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = nullptr;
	}
}
//��ʼ������
bool UdpMediator::OpenNet()
{
	return m_pNet->InitNet();
}
//�ر�����
void UdpMediator::CloseNet()
{
	m_pNet->UinitNet();
}
//������Ϣ
bool UdpMediator::SendData(char* buf, int len, long Ip)
{
	return m_pNet->SendData(buf, len, Ip);
}
//������Ϣ
void UdpMediator::AcceptData(char* buf, int len, long Ip)
{
	cout << buf << endl;
}