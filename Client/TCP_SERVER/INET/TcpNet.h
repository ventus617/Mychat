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
	//初始化网络
	 bool InitNet() override;
	//关闭网络
	 void UinitNet() override;
	//发送信息
	 bool SendData(char* buf, int len, long Ip) override;
	//接收信息
	 void AcceptData() override;

protected:
	SOCKET m_sock;
	// 保存客户端和对应的socket，key是线程ID
	map<unsigned int, SOCKET> m_mapThreadIDtoSocket;
	// 保存线程的句柄
	list<HANDLE> m_hThreadHandleList;
	bool m_isStop;
	// 因为监听就不能接受数据，因此要分开
	// 接收监听的线程
	static unsigned int __stdcall AcceptThread(void* lpVoid);
	// 接收数据的线程
	static unsigned int __stdcall RecvThread(void* lpVoid);
};