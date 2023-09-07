#include"TcpClient.h"
#include"../Mediator/TcpMediator.h"
#include<process.h>


//构造
TcpClient::TcpClient(INetMediator* m_p):m_sock(INVALID_SOCKET),m_isStop(false),m_handle(nullptr)
{
	m_pMediator = m_p;
}
//析构
TcpClient::~TcpClient()
{
    UinitNet();
}
//初始化网络
bool TcpClient::InitNet()
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
        qDebug() << "socket error:" << WSAGetLastError();
        return false;
    }
    else
    {
       qDebug() << "create socket successfully";
    }
    //设置套接字
    //设置客户端发送缓冲区
         int nSendBuf=64*1024;//设置为64K
         setsockopt(m_sock,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
    //设置客户端接收缓冲区
         int nRecvBuf=64*1024;//设置为64K
         setsockopt(m_sock,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));

    DWORD nNetTimeout= 1500;//1秒 - 1000

    //发送时限 , 超时退出避免长时间阻塞
    setsockopt(m_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(DWORD));

    //禁用 TCP-NODELAY
    int value = 1;
    setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (char *)&value, sizeof(int));
    //3.向服务端发起连接
    sockaddr_in ClientAddr;
    ClientAddr.sin_family = AF_INET;
    ClientAddr.sin_port = htons(TCP_PORT);
    ClientAddr.sin_addr.S_un.S_addr = inet_addr(TCP_SERVER_IP);

    err=connect(m_sock,(SOCKADDR*)&ClientAddr,sizeof(ClientAddr));
    if(m_sock==INVALID_SOCKET)
    {
        qDebug()<<"connect fail:"<<WSAGetLastError();
        return false;
    }
    else
    {
        qDebug()<<"connect successfully";
    }

    //4.创建接收数据的线程(accept返回的socket用来与当前连接成功的客户端进行数据通信)
     m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
    if (!m_handle)
    {
        qDebug() << "create acceptthread failed" ;
        return false;
    }
    return true;

}
//卸载网络
void TcpClient::UinitNet()
{
    m_isStop = true;
    //1.结束线程
    if (m_handle)
    {
        if (WAIT_TIMEOUT == WaitForSingleObject(m_handle, 100))
        {
            TerminateThread(m_handle, -1);
        }
        CloseHandle(m_handle);
        m_handle = nullptr;
    }
    //2.关闭套接字
    if (m_sock && m_sock != INVALID_SOCKET)
    {
        closesocket(m_sock);
    }
    //3.卸载库
    WSACleanup();
}
//发送数据
bool TcpClient::SendData(char*buf,int len,long Ip)
{
    //1.校验参数
    if (!buf || len <= 0)
    {
        qDebug() << "TcpNet::SendData error" ;
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
    if (send(m_sock, pbuf, len + 4, 0) <= 0)
    {
        qDebug() << "TcpNet::SendData error:" << WSAGetLastError() ;
        delete pbuf;
        pbuf = nullptr;
        return false;
    }
    delete []pbuf;
    pbuf = nullptr;
    return true;

}
//接收数据
void TcpClient::AcceptData()
{

    //1.一对一关系，获取连接成功的socket
    SOCKET sock = m_sock;
    if (!sock || INVALID_SOCKET == sock)
    {
        qDebug() << "TcpNet::RecvData sock error" ;
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
            qDebug() << "TcpNet::RecvData error:" << WSAGetLastError() ;
            break;
        }
    }
}
//接收数据线程
unsigned int __stdcall TcpClient::RecvThread(void* lpVoid)
{
    TcpClient* pthis = (TcpClient*)lpVoid;
    pthis->AcceptData();
    return 0;
}
