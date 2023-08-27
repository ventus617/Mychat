#include"TcpClient.h"
#include"../Mediator/TcpMediator.h"
#include<process.h>


//����
TcpClient::TcpClient(INetMediator* m_p):m_sock(INVALID_SOCKET),m_isStop(false),m_handle(nullptr)
{
	m_pMediator = m_p;
}
//����
TcpClient::~TcpClient()
{
    UinitNet();
}
//��ʼ������
bool TcpClient::InitNet()
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
        qDebug() << "socket error:" << WSAGetLastError();
        return false;
    }
    else
    {
       qDebug() << "create socket successfully";
    }
    //3.�����˷�������
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
    //4.�����������ݵ��߳�(accept���ص�socket�����뵱ǰ���ӳɹ��Ŀͻ��˽�������ͨ��)
     m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, this, 0, NULL);
    if (!m_handle)
    {
        qDebug() << "create acceptthread failed" ;
        return false;
    }
    return true;

}
//ж������
void TcpClient::UinitNet()
{
    m_isStop = true;
    //1.�����߳�
    if (m_handle)
    {
        if (WAIT_TIMEOUT == WaitForSingleObject(m_handle, 100))
        {
            TerminateThread(m_handle, -1);
        }
        CloseHandle(m_handle);
        m_handle = nullptr;
    }
    //2.�ر��׽���
    if (m_sock && m_sock != INVALID_SOCKET)
    {
        closesocket(m_sock);
    }
    //3.ж�ؿ�
    WSACleanup();
}
//��������
bool TcpClient::SendData(char*buf,int len,long Ip)
{
    //1.У�����
    if (!buf || len <= 0)
    {
        qDebug() << "TcpNet::SendData error" ;
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
//��������
void TcpClient::AcceptData()
{

    //1.һ��һ��ϵ����ȡ���ӳɹ���socket
    SOCKET sock = m_sock;
    if (!sock || INVALID_SOCKET == sock)
    {
        qDebug() << "TcpNet::RecvData sock error" ;
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
            qDebug() << "TcpNet::RecvData error:" << WSAGetLastError() ;
            break;
        }
    }
}
//���������߳�
unsigned int __stdcall TcpClient::RecvThread(void* lpVoid)
{
    TcpClient* pthis = (TcpClient*)lpVoid;
    pthis->AcceptData();
    return 0;
}
