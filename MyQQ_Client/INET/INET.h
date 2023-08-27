#pragma once
#include<iostream>
#include<winsock.h>
using namespace std;

class INetMediator;
//�н���ģʽ���û�A����Ϊ�ײ�����ĸ���
class INet//
{
public:
	INet(){}
	virtual ~INet(){}//��Ϊ�Ǹ��࣬��Ϊ�ӿ��࣬���������
public:
	//��ʼ������
	virtual bool InitNet() = 0;
	//�ر�����
	virtual void UinitNet() = 0;
	//������Ϣ
	virtual bool SendData(char* buf, int len, long Ip) = 0;
protected:
	//������Ϣ
	virtual void AcceptData() = 0;
	INetMediator* m_pMediator;
};
