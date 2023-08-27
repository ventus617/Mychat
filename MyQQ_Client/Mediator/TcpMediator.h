#pragma once
#include"INetMediator.h"

class TcpClientMediator :public INetMediator
{
    Q_OBJECT
public:
    TcpClientMediator();
    ~TcpClientMediator();
public:
	//��ʼ������
	 bool OpenNet() override;
	//�ر�����
	 void CloseNet() override;
	//��������
	 bool SendData(char* buf, int nlen, long Ip) override;
	//��������
	 void AcceptData(char* buf, int nlen, long Ip) override;

signals:
     //�������ݸ�kernel
     void SIG_readData(char*buf,int nlen,long Ip);
};
