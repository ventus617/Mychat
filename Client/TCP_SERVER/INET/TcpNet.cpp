#include"TcpNet.h"
#include"../Mediator/TcpMediator.h"

//构造
TcpNet::TcpNet(INetMediator* m_p):m_sock(INVALID_SOCKET),m_isStop(false)
{
	m_pMediator = m_p;
}
//析构
TcpNet::~TcpNet()
{
    UinitNet();
}
//初始化网络
bool TcpNet::InitNet()
{
    // 1、选项目————加载库
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
    //2.创建套接字
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
    //3.分配IP地址
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
    //4.监听
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
    //5.创建接收连接的线程(accept返回的socket用来与当前连接成功的客户端进行数据通信)
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
//卸载网络
void TcpNet::UinitNet()
{
    m_isStop = true;
    //1.结束线程
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
    //2.关闭套接字
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
    //3.卸载库
    WSACleanup();
}
//发送数据
bool TcpNet::SendData(char*buf,int len,long Ip)
{
    //1.校验参数
    if (!buf || len <= 0)
    {
        cout << "TcpNet::SendData error" << endl;
        return false;
    }
    //2.将包长度和包内容一起打包发送
    char* pbuf = new char[len+4];
    memset(pbuf, 0, len + 4);
    //写入包大小
    int* plen = reinterpret_cast<int*>(pbuf);
    *plen = len;
    //写入包内容
    char* ppbuf = pbuf;
    ppbuf += 4;
    memcpy(ppbuf, buf, len);
    //发送数据包
    if (send(Ip, pbuf, len + 4, 0) <= 0)
    {
        cout << "TcpNet::SendData error:" << WSAGetLastError() << endl;
        delete []pbuf;
        pbuf = nullptr;
        return false;
    }
    return true;

}
//接收数据
void TcpNet::AcceptData()
{
    //因为创建线程就立刻执行，但是map存入socket需要时间，等待时间
    Sleep(100);
    //1.一对一关系，获取连接成功的socket
    SOCKET sock = m_mapThreadIDtoSocket[GetCurrentThreadId()];
    if (!sock || INVALID_SOCKET == sock)
    {
        cout << "TcpNet::RecvData sock error" << endl;
        return;
    }
    //2.接收数据
    int nRecvNum = 0;
    int nPackSize = 0;
    
    //使用偏移量，记录累计读取了多少数据
    int offset = 0;
    while (!m_isStop)
    {
        offset = 0;
        //接收包长度,包长度放在nPackSize中
        nRecvNum = recv(sock, (char*)&nPackSize, sizeof(int), 0);
        if (nRecvNum > 0)
        {
            char* recvBuf = new char[nPackSize];
            //接收包内容
            while (nPackSize > 0)
            {
                nRecvNum = recv(sock, recvBuf + offset, nPackSize, 0);
                if (nRecvNum > 0)
                {
                    offset += nRecvNum;
                    nPackSize -= nRecvNum;
                }
            }
            //发送给中介者类，接收完数据了，就交给核心类去处理数据
            m_pMediator->AcceptData(recvBuf, offset, sock);
        }
        else
        {
            cout << "TcpNet::RecvData error:" << WSAGetLastError() << endl;
            break;
        }
    }
}
//接收连接线程
unsigned int _stdcall TcpNet::AcceptThread(void* lpVoid)
{
    TcpNet* Pthis = (TcpNet*)lpVoid;
    //定义接收的客户端结构体
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
        
        //创建接收数据的线程，一对一
        HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, Pthis, 0, &threadId);
        if (handle)
        {
            Pthis->m_hThreadHandleList.push_back(handle);
        }

        //将socket保存在map中,利用线程ID不同来存储不同的sock，就能通过数据接收线程ID得到对应客户端的sock
        Pthis->m_mapThreadIDtoSocket[threadId] = sock;
    }
    return 0;
}
//接收数据线程
unsigned int _stdcall TcpNet::RecvThread(void* lpVoid)
{
    TcpNet* pthis = (TcpNet*)lpVoid;
    pthis->AcceptData();
    return 0;
}