#pragma once
#include"INET.h"
#include"config.h"
#include<process.h>
#include<queue>
class UdpNet :public INet
{
public:
	UdpNet(INetMediator* pMediator);//�н���ģʽ����Ҫһ���н���,���Ĵ������н��߲�����
	//���˵��ͨ��new�ķ�ʽ����ȡ�����Ȼᷢ��ѭ�����죬ջ���(A�Ĺ�����Ҫ�ȹ���B��B�Ĺ�������Ҫ����A�����湹��)
	//��Σ������ã������һ���ײ�ʹ���һ���µ��н��ߣ���ô�н��߾���һ������ƥ��һ�����������ˣ�������һ����ƥ�����࣬����ʵ��һ���н�����Զ���ײ���д���������
	~UdpNet()override;
public:
	bool InitNet()override;
	//�ر�����
	 void UinitNet()override;
	//������Ϣ
	 bool SendData(char* buf, int len, long Ip)override;
protected:
	//�������ݵ��߳� static ��δ���������ʱ�򣬾���Ҫʹ�þ�̬��Ա����
	static unsigned int _stdcall RecvThread(void* lpVoid);
	//�������� 
	void AcceptData()override;
	//�رշ�����
	void SetStop();
	SOCKET m_sock;//�Լ����׽���
	HANDLE m_handle;//�߳̾��
	bool m_stop;//������ֹͣ����

};