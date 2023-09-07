#include"UdpNet.h"
#include"UdpMediator.h"
//����
UdpNet::UdpNet(INetMediator* m_pINetMediator):m_sock(INVALID_SOCKET),m_handle(nullptr),m_stop(false)
{
	m_pMediator = m_pINetMediator;//ͨ��ʹ���вι��죬�Ϳ��Ի���н��߶���
}
//����
UdpNet::~UdpNet()
{
	UinitNet();
}
//��ʼ������
bool UdpNet::InitNet()
{
	//1.���ؿ�
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
		WSACleanup();//��֧�ֵĻ��������
		return false;
	}
	else
		printf("The Winsock 2.2 dll was found okay\n");
	//2.�����׽���
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
	//3.�󶨵�ַ
	//������ַ�ṹ��
	sockaddr_in addServer;
	//����Э����
	addServer.sin_family = AF_INET;
	//����˿ں�
	addServer.sin_port = htons(UDP_PORT);
	//����ip��ַ
	addServer.sin_addr.S_un.S_addr = INADDR_ANY;
	//����ip��ַ
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
	//4.����Ȩ��
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
	//5.�����߳�����������,��Ϊ�������ݺͽ�������֮����г�ͻ
	m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
	return true;
}

//�ر�����
void UdpNet::UinitNet()
{
	//�����̹߳��� 
	if (m_stop == false)m_stop = true;
	if (m_handle)
	{
		if (WaitForSingleObject(m_handle, 1000) == WAIT_TIMEOUT)
		{
			TerminateThread(m_handle, -1);
		}
		//���վ��
		CloseHandle(m_handle);
		m_handle = nullptr;
	}
	//�ر��׽���
	if (m_sock != INVALID_SOCKET && m_sock)
	{
		closesocket(m_sock);
	}
	//ж�ؿ�
	WSACleanup();
}
//������Ϣ
bool UdpNet::SendData(char* buf, int len, long Ip)
{
	//���巢�ͽṹ��
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
//������Ϣ
void UdpNet::AcceptData()
{
	char recvBuf[UDP_RECVBUF];
	memset(recvBuf, 0, UDP_RECVBUF);
	//������սṹ��
	sockaddr_in recvadd;
	int addlen = sizeof(recvadd);
	int RecvNum = 0;
	while (!m_stop)
	{
		//���ؽ��յ������ݳ���
		RecvNum = recvfrom(m_sock, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&recvadd, &addlen);
		if (RecvNum > 0)
		{
			//�ȵõ����ݳ��ȣ���������ݣ��ٰ������ݵĶ��������н���
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

//�������ݵ��߳�
unsigned int _stdcall UdpNet::RecvThread(void* lpVoid)
{
	UdpNet* pthis = (UdpNet*)lpVoid;
	pthis->AcceptData();//���߳̽��պ�����Ϊ��ȥ������Ľ������ݺ���

	//��ֱ�Ӱѽ������ݺ�����������Ϊ����Ҫչʾ����һ�����յĽӿڣ������Ǳ�������һ���̺߳�������
	return 1;
}

