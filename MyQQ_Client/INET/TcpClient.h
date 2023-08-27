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
	// 保存线程的句柄
    HANDLE m_handle;
	bool m_isStop;
	// 接收数据的线程
	static unsigned int __stdcall RecvThread(void* lpVoid);
};
