#include"TcpNet.h"
#include"../Mediator/TcpMediator.h"

//����
TcpNet::TcpNet(INetMediator* m_p):m_sock(INVALID_SOCKET),m_isStop(false)
{
	m_pMediator = m_p;
}
//����
TcpNet::~TcpNet()
{
    UinitNet();
}
//��ʼ������
bool TcpNet::InitNet()
{
    // 1��ѡ��Ŀ�����������ؿ�
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        return false;
    } if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        printf("Could not find a usable version of Winsock.dll\n");
        return false;
    }
    else printf("The Winsock 2.2 dll was found okay\n");
    //2.�����׽���
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock == INVALID_SOCKET)
    {
        cout << "socket error:" << WSAGetLastError() << endl;
        return false;
    }
    else
    {
        cout << "create socket successfully" << endl;
    }
    //3.����IP��ַ
    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(TCP_PORT);
    addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
    err = bind(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
    if (err == SOCKET_ERROR)
    {
        cout << "bind error:" << WSAGetLastError() << endl;
        return false;
    }
    else
    {
        cout << "bind socket successfully" << endl;
    }
    //4.����
    listen(m_sock, BACK_LOG);
    if (err == SOCKET_ERROR)
    {
        cout << "listen error:" << WSAGetLastError() << endl;
        return false;
    }
    else
    {
        cout << "listen successfully" << endl;
    }
    //5.�����������ӵ��߳�(accept���ص�socket�����뵱ǰ���ӳɹ��Ŀͻ��˽�������ͨ��)
    HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &AcceptThread, this, 0, NULL);
    if (handle)
    {
        m_hThreadHandleList.push_back(handle);
    }
    else
    {
        cout << "create acceptthread failed" << endl;
        return false;
    }
    return true;
  
}
//ж������
void TcpNet::UinitNet()
{
    m_isStop = true;
    //1.�����߳�
    m_isStop = true;
    for (auto ite = m_hThreadHandleList.begin(); ite != m_hThreadHandleList.end();)
    {
        HANDLE handle = *ite;
        if (handle)
        {
            if (WAIT_TIMEOUT == WaitForSingleObject(handle, 100))
            {
                TerminateThread(handle, -1);
            }
            CloseHandle(handle);
            handle = nullptr;
        }
        ite = m_hThreadHandleList.erase(ite);
    }
    //2.�ر��׽���
    for (auto ite = m_mapThreadIDtoSocket.begin(); ite != m_mapThreadIDtoSocket.end();)
    {
        SOCKET sock = ite->second;
        if (sock && sock != INVALID_SOCKET)
        {
            closesocket(sock);
        }
        ite = m_mapThreadIDtoSocket.erase(ite);
    }
    if (m_sock && m_sock != INVALID_SOCKET)
    {
        closesocket(m_sock);
    }
    //3.ж�ؿ�
    WSACleanup();
}
//��������
bool TcpNet::SendData(char*buf,int len,long Ip)
{
    //1.У�����
    if (!buf || len <= 0)
    {
        cout << "TcpNet::SendData error" << endl;
        return false;
    }
    //2.�������ȺͰ�����һ��������
    char* pbuf = new char[len+4];
    memset(pbuf, 0, len + 4);
    //д�����С
    int* plen = reinterpret_cast<int*>(pbuf);
    *plen = len;
    //д�������
    char* ppbuf = pbuf;
    ppbuf += 4;
    memcpy(ppbuf, buf, len);
    //�������ݰ�
    if (send(Ip, pbuf, len + 4, 0) <= 0)
    {
        cout << "TcpNet::SendData error:" << WSAGetLastError() << endl;
        delete []pbuf;
        pbuf = nullptr;
        return false;
    }
    return true;

}
//��������
void TcpNet::AcceptData()
{
    //��Ϊ�����߳̾�����ִ�У�����map����socket��Ҫʱ�䣬�ȴ�ʱ��
    Sleep(100);
    //1.һ��һ��ϵ����ȡ���ӳɹ���socket
    SOCKET sock = m_mapThreadIDtoSocket[GetCurrentThreadId()];
    if (!sock || INVALID_SOCKET == sock)
    {
        cout << "TcpNet::RecvData sock error" << endl;
        return;
    }
    //2.��������
    int nRecvNum = 0;
    int nPackSize = 0;
    
    //ʹ��ƫ��������¼�ۼƶ�ȡ�˶�������
    int offset = 0;
    while (!m_isStop)
    {
        offset = 0;
        //���հ�����,�����ȷ���nPackSize��
        nRecvNum = recv(sock, (char*)&nPackSize, sizeof(int), 0);
        if (nRecvNum > 0)
        {
            char* recvBuf = new char[nPackSize];
            //���հ�����
            while (nPackSize > 0)
            {
                nRecvNum = recv(sock, recvBuf + offset, nPackSize, 0);
                if (nRecvNum > 0)
                {
                    offset += nRecvNum;
                    nPackSize -= nRecvNum;
                }
            }
            //���͸��н����࣬�����������ˣ��ͽ���������ȥ��������
            m_pMediator->AcceptData(recvBuf, offset, sock);
        }
        else
        {
            cout << "TcpNet::RecvData error:" << WSAGetLastError() << endl;
            break;
        }
    }
}
//���������߳�
unsigned int _stdcall TcpNet::AcceptThread(void* lpVoid)
{
    TcpNet* Pthis = (TcpNet*)lpVoid;
    //������յĿͻ��˽ṹ��
    sockaddr_in addrClient;
    int addrClientLen = sizeof(addrClient);
    unsigned int threadId = 0;
    while (!Pthis->m_isStop)
    {
        SOCKET sock = accept(Pthis->m_sock, (sockaddr*)&addrClient, &addrClientLen);
        if (sock == INVALID_SOCKET)
        {
            cout << "accept failed ,error:" << WSAGetLastError() << endl;
            continue;
        }
        cout << "TcpNet::AcceptThread ClientIp:" << inet_ntoa(addrClient.sin_addr) << endl;
        
        //�����������ݵ��̣߳�һ��һ
        HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, Pthis, 0, &threadId);
        if (handle)
        {
            Pthis->m_hThreadHandleList.push_back(handle);
        }

        //��socket������map��,�����߳�ID��ͬ���洢��ͬ��sock������ͨ�����ݽ����߳�ID�õ���Ӧ�ͻ��˵�sock
        Pthis->m_mapThreadIDtoSocket[threadId] = sock;
    }
    return 0;
}
//���������߳�
unsigned int _stdcall TcpNet::RecvThread(void* lpVoid)
{
    TcpNet* pthis = (TcpNet*)lpVoid;
    pthis->AcceptData();
    return 0;
}