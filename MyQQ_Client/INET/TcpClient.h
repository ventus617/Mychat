#include"INET.h"
#include<map>
#include<list>
#include<process.h>
#include"../config/config.h"
#include<QDebug>
class TcpClient :public INet
{
public:
    TcpClient(INetMediator* m_p);
    ~TcpClient();
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
	// �����̵߳ľ��
    HANDLE m_handle;
	bool m_isStop;
	// �������ݵ��߳�
	static unsigned int __stdcall RecvThread(void* lpVoid);
};
