#include"UdpNet.h"
#include"UdpMediator.h"
//构造
UdpNet::UdpNet(INetMediator* m_pINetMediator):m_sock(INVALID_SOCKET),m_handle(nullptr),m_stop(false)
{
	m_pMediator = m_pINetMediator;//通过使用有参构造，就可以获得中介者对象
}
//析构
UdpNet::~UdpNet()
{
	UinitNet();
}
//初始化网络
bool UdpNet::InitNet()
{
	//1.加载库
	WORD wVersion;
	WSADATA wsaData;
	int error;

	wVersion = MAKEWORD(2, 2);
	error = WSAStartup(wVersion, &wsaData);
	if (error != 0)
	{
		cout << "WSAStartup failed with error:" << errno << endl;
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		printf("Could not find a usable version of Winsock.dll\n");
		WSACleanup();//不支持的话就清理库
		return false;
	}
	else
		printf("The Winsock 2.2 dll was found okay\n");
	//2.创建套接字
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_sock == INVALID_SOCKET)
	{
		cout << "socket error:" << WSAGetLastError() << endl;
		WSACleanup();
		return false;
	}
	else
	{
		cout << "create socket successfully" << endl;
	}
	//3.绑定地址
	//创建地址结构体
	sockaddr_in addServer;
	//分配协议族
	addServer.sin_family = AF_INET;
	//分配端口号
	addServer.sin_port = htons(UDP_PORT);
	//分配ip地址
	addServer.sin_addr.S_un.S_addr = INADDR_ANY;
	//分配ip地址
	error = bind(m_sock, (sockaddr*)&addServer, sizeof(addServer));
	if (error == SOCKET_ERROR)
	{
		cout << "bind error:" << WSAGetLastError() << endl;
		closesocket(m_sock);
		WSACleanup();
		return false;
	}
	else
	{
		cout << "bind successfully" << endl;
	}
	//4.申请权限
	bool val = true;
	error = setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (char*)&val, sizeof(val));
	if (error != 0)
	{
		cout << "setsocketopt error:" << WSAGetLastError() << endl;
	}
	else
	{
		cout << "setsockopt successfully" << endl;
	}
	//5.创建线程来接收数据,因为发送数据和接收数据之间会有冲突
	m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}

//关闭网络
void UdpNet::UinitNet()
{
	//结束线程工作 
	if (m_stop == false)m_stop = true;
	if (m_handle)
	{
		if (WaitForSingleObject(m_handle, 1000) == WAIT_TIMEOUT)
		{
			TerminateThread(m_handle, -1);
		}
		//回收句柄
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
	//关闭套接字
	if (m_sock != INVALID_SOCKET && m_sock)
	{
		closesocket(m_sock);
	}
	//卸载库
	WSACleanup();
}
//发送消息
bool UdpNet::SendData(char* buf, int len, long Ip)
{
	//定义发送结构体
	sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(UDP_PORT);
	client.sin_addr.S_un.S_addr = Ip;
	if (sendto(m_sock, buf, len, 0, (sockaddr*)&client, sizeof(client)) <= 0)
	{
		cout << "SendData error:" << WSAGetLastError() << endl;
		return false;
	}
	return true;
}
//接收消息
void UdpNet::AcceptData()
{
	char recvBuf[UDP_RECVBUF];
	memset(recvBuf, 0, UDP_RECVBUF);
	//定义接收结构体
	sockaddr_in recvadd;
	int addlen = sizeof(recvadd);
	int RecvNum = 0;
	while (!m_stop)
	{
		//返回接收到的数据长度
		RecvNum = recvfrom(m_sock, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&recvadd, &addlen);
		if (RecvNum > 0)
		{
			//先得到数据长度，存放新内容，再把新内容的东西传给中介者
			char* packBuf = new char[RecvNum];
			memcpy(packBuf, recvBuf, RecvNum);
			m_pMediator->AcceptData(packBuf, RecvNum, recvadd.sin_addr.S_un.S_addr);
		}
		else if(RecvNum<0)
		{
			cout << "recvfrom error:" << WSAGetLastError() << endl;
		}
		
	}
}

//接收数据的线程
unsigned int _stdcall UdpNet::RecvThread(void* lpVoid)
{
	UdpNet* pthis = (UdpNet*)lpVoid;
	pthis->AcceptData();//该线程接收函数是为了去调用类的接收数据函数

	//不直接把接收数据函数给他是因为我需要展示我有一个接收的接口，而不是被隐藏在一个线程函数里面
	return 1;
}

