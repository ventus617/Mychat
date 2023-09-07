#pragma once
#include<iostream>
using namespace std;
//�н���ģʽ���н���
class INet;//������߻�����ϵ�������ظ��������⣬��ֱ��ʹ���������ɣ�����Ҫʹ��ͷ�ļ�
class INetMediator
{
public:
	INetMediator(){}
	virtual ~INetMediator(){}
public:
	//��ʼ������
	virtual bool OpenNet() = 0;
	//�ر�����
	virtual void CloseNet() = 0;
	//��������
	virtual bool SendData(char* buf, int nlen, long Ip) = 0;
	//��������
	virtual void AcceptData(char* buf, int nlen, long Ip) = 0;
protected:
	INet* m_pNet;
};