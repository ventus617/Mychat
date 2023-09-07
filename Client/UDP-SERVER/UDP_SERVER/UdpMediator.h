#pragma once
#include"INetMediator.h"
#include"config.h"
class UdpMediator :public INetMediator
{
public:
	UdpMediator();
	~UdpMediator()override;
public:
	//��ʼ������
	bool OpenNet()override;
	//�ر�����
	void CloseNet()override;
	//��������
	bool SendData(char* buf, int nlen, long Ip)override;
	//��������,�ײ��յ������ݻ�õ�ip��������Ϊ���εķ�ʽ�����н���
	void AcceptData(char* buf, int nlen, long Ip)override;
};