#pragma once
#include"INetMediator.h"

class TcpMediator :public INetMediator
{
public:
	TcpMediator();
	~TcpMediator();
public:
	//��ʼ������
	 bool OpenNet() override;
	//�ر�����
	 void CloseNet() override;
	//��������
	 bool SendData(char* buf, int nlen, long Ip) override;
	//��������
	 void AcceptData(char* buf, int nlen, long Ip) override;
};