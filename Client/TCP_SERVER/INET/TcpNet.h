#include"INET.h"
#include<map>
#include<list>
#include<process.h>
#include"../config/config.h"

class TcpNet :public INet
{
public:
	TcpNet(INetMediator* m_p);
	~TcpNet();
public:
	//��ʼ������
	 bool InitNet() override;
	//�ر�����
	 void UinitNet() override;
	//������Ϣ
	 bool SendData(char* buf, int len, long Ip) override;
	//������Ϣ
	 void AcceptData() override;

protected:
	SOCKET m_sock;
	// ����ͻ��˺Ͷ�Ӧ��socket��key���߳�ID
	map<unsigned int, SOCKET> m_mapThreadIDtoSocket;
	// �����̵߳ľ��
	list<HANDLE> m_hThreadHandleList;
	bool m_isStop;
	// ��Ϊ�����Ͳ��ܽ������ݣ����Ҫ�ֿ�
	// ���ռ������߳�
	static unsigned int __stdcall AcceptThread(void* lpVoid);
	// �������ݵ��߳�
	static unsigned int __stdcall RecvThread(void* lpVoid);
};