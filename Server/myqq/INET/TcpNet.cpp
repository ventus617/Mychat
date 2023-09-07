<<<<<<< HEAD
#include"TcpNet.h"
#include"../Mediator/TcpMediator.h"
//设置分离态线程属性
static int epfd;
static pthread_attr_t thread_attr;

//构造
TcpNet::TcpNet(INetMediator* m_p):m_sock(-1),m_isStop(false),tp(nullptr),send_tp(nullptr)
{
	m_pMediator = m_p;
}
//析构
TcpNet::~TcpNet()
{
    TP_Destroy();
    UinitNet();
}
//初始化网络
bool TcpNet::InitNet()
{
    //2.创建套接字
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock == -1)
    {
        cout << "socket error:" << strerror(errno) << endl;
        return false;
    }
    else
    {
        cout << "create socket successfully" << endl;
    }
    //设置非阻塞
    int flag=fcntl(m_sock,F_GETFL,0);
    flag |= O_NONBLOCK;
    fcntl(m_sock,F_SETFL,flag);
    //3.分配IP地址
    struct sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(TCP_PORT);
    addrServer.sin_addr.s_addr = INADDR_ANY;
    int err;
    err = bind(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
    if (err !=0)
    {
        cout << "bind error:" <<strerror(errno) << endl;
        return false;
    }
    else
    {
        cout << "bind socket successfully" << endl;
    }
    //4.监听
    listen(m_sock, BACK_LOG);
    if (err == -1)
    {
        cout << "listen error:" << strerror(errno)<< endl;
        return false;
    }
    else
    {
        cout << "listen successfully" << endl;
    }
    //5.创建接受线程池+发送线程池
    if(((tp=TP_Create())==nullptr)||((send_tp=TP_Send_Create())==nullptr))
    {
        return false;
    }
    return true;
  
}
//卸载网络
void TcpNet::UinitNet()
{
    for(auto ite=sockset.begin();ite!=sockset.end();)
    {
        close(*ite);
        ite=sockset.erase(ite);
    }
    m_isStop = true;
    if (m_sock && m_sock != -1)
    {
        close(m_sock);
    }
}

//接收数据
void TcpNet::AcceptData()
{
}

void TcpNet::Eventloop()
{
    //建立epoll
    TP_Epoll_Create();
    //加载监听
    TP_Epoll_Listen();
    //监听到位后，进行业务处理
}

void *MySendData(void *arg)
{
    send_t *st=(send_t*)arg;
    //1.校验参数
    if (!st->buf || st->len <= 0)
    {
        cout << "TcpNet::SendData error" << endl;
        return NULL;
    }
    //2.将包长度和包内容一起打包发送
    char* pbuf = new char[st->len+4];
    memset(pbuf, 0, st->len + 4);
    //写入包大小
    int* plen = reinterpret_cast<int*>(pbuf);
    *plen = st->len;
    //写入包内容
    char* ppbuf = pbuf;
    ppbuf += 4;
    memcpy(ppbuf, st->buf, st->len);
    //发送数据包
    if (send(st->sock, pbuf, st->len + 4, 0) <= 0)
    {
        cout << "TcpNet::SendData error:" << strerror(errno) << endl;
        delete[]pbuf;
        pbuf=nullptr;
    }
    delete st;
    st=nullptr;
    return NULL;
}
//发送数据
bool TcpNet::SendData(char*buf,int len,long Ip)
{
    bs_t bs;
    send_t* st=(send_t*)malloc(sizeof(send_t));
    if(len>TCP_RECVBUF)
    {
        printf("send error: send len out of range\n");
        return false;
    }
    memcpy(st->buf,buf,len);
    st->len=len;
    st->sock=Ip;
    bs.Business_Addr=MySendData;
    bs.arg=(void*)st;
    TP_Producer(bs,send_tp);
    return true;
}
void* TcpNet::TP_Customer(void *arg)
{
    tp_t*tp=(tp_t*)arg;
    while(tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&tp->queue_lock);
        while (tp->Cur==0) {
            pthread_cond_wait(&tp->Not_Empty,&tp->queue_lock);
            pthread_mutex_lock(&tp->var_lock);
            if(tp->Thread_flag>0)
            {
                pthread_mutex_unlock(&tp->queue_lock);
                tp->Thread_flag--;
                tp->Thread_Alive--;
                //printf("pthread 0x%x exit... thread_flag:%d \n ",(unsigned int)pthread_self(),tp->Thread_flag);
                pthread_mutex_unlock(&tp->var_lock);
                pthread_exit(NULL);
            }
            pthread_mutex_unlock(&tp->var_lock);
        }
        if(tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&tp->queue_lock);
            printf("TP_Customer Thread_Shutdown error\n");
            break;
        }
        //printf("Get Work,0x%x is Working\n",(unsigned int)pthread_self());
        bs_t bs;
        bs.Business_Addr=tp->Container[tp->Rear].Business_Addr;
        bs.arg=tp->Container[tp->Rear].arg;
        tp->Cur--;
        tp->Rear=(tp->Rear+1)%tp->Max;
        pthread_cond_signal(&tp->Not_Full);
        pthread_mutex_unlock(&tp->queue_lock);
        pthread_mutex_lock(&tp->var_lock);
        tp->Thread_Busy++;
        tp->Thread_Alive--;
        pthread_mutex_unlock(&tp->var_lock);
        bs.Business_Addr(bs.arg);
        pthread_mutex_lock(&tp->var_lock);
        tp->Thread_Busy--;
        tp->Thread_Alive++;
        pthread_mutex_unlock(&tp->var_lock);
    }
    printf("Customer Thread 0x%x Shutdown \n",(unsigned int)pthread_self());
    pthread_exit(NULL);
}

void *TcpNet::TP_SEND_Customer(void *arg)
{
    send_poll_t *send_tp=(send_poll_t*)arg;
    while(send_tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&send_tp->queue_lock);
        while (send_tp->Cur==0) {
            pthread_cond_wait(&send_tp->Not_Empty,&send_tp->queue_lock);
        }
        if(send_tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&send_tp->queue_lock);
            printf("TP_SEND_Customer Thread_Shutdown error\n");
            break;
        }
        printf("Send Work,0x%x is Working\n",(unsigned int)pthread_self());
        bs_t bs;
        bs.Business_Addr=send_tp->Container[send_tp->Rear].Business_Addr;
        bs.arg=send_tp->Container[send_tp->Rear].arg;
        send_tp->Cur--;
        send_tp->Rear=(send_tp->Rear+1)%send_tp->Max;
        pthread_cond_signal(&send_tp->Not_Full);
        pthread_mutex_unlock(&send_tp->queue_lock);
        bs.Business_Addr(bs.arg);
    }
    printf("SEND_Customer Thread 0x%x Shutdown \n",(unsigned int)pthread_self());
    pthread_exit(NULL);
}
int IF_THREAD_ALIVE(pthread_t tid)
{
    int err;
    if((err=pthread_kill(tid,0))==ESRCH)
    {
        return 0;
    }
    return 1;
}
void* TcpNet::TP_Manager(void *arg)
{
    tp_t*tp=(tp_t*)arg;
    double state;
    int addflag;
    int alive;
    int busy;
    int flag;
    int Max;
    int Min;
    int add;
    int Cur;
    int Thread_Cur=0;
    while(tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&tp->var_lock);
        alive=tp->Thread_Alive;
        busy=tp->Thread_Busy;
        flag=tp->Thread_flag;
        Max=tp->Thread_Max;
        Min=tp->Thread_Min;
        Cur=tp->Cur;
        pthread_mutex_unlock(&tp->var_lock);
        state=(double)busy/(alive+busy)*100;
        Thread_Cur=alive+busy;
        //printf("Busy Thread Number:%d,Alive Thread Number:%d,State:%2.lf\n",busy,alive,state);
        while(flag)
        {
            pthread_mutex_lock(&tp->var_lock);
            flag=tp->Thread_flag;
            pthread_mutex_unlock(&tp->var_lock);
            //printf("Wait For Thread Exit,Flag %d\n",flag);
            sleep(1);
        }
        //如果大于70就扩容
        if(state>=70&&(Thread_Cur+_INCREASE_THREAD)<Max)
        {
            //printf("Increase Thread Number\n");
            for(addflag=0, add=0;addflag<tp->Thread_Max&&add<_INCREASE_THREAD;addflag++)
            {
                if(tp->cus_tids[addflag]==0||(IF_THREAD_ALIVE(tp->cus_tids[addflag])!=0))
                {
                    int err;
                    if((err=pthread_create(&tp->cus_tids[addflag],&thread_attr,TP_Customer,(void*)tp))>0)
                    {
                            printf("TP_Manager,Create Customer Thread Failed%s\n",strerror(err));
                            exit(0);
                    }
                    add++;
                    pthread_mutex_lock(&tp->var_lock);
                    tp->Thread_Alive++;
                    pthread_mutex_unlock(&tp->var_lock);
                }
            }
           //printf("Manager Thread 0x%x,Create New Thread Successfully..\n",(unsigned int)pthread_self());
        }
        //如果闲置线程大于2倍就缩减，或者闲置占比比较高就缩减
        if(state<=20&&Thread_Cur-_THREAD_REDUCE>=Min)
        {
            pthread_mutex_lock(&tp->var_lock);
            tp->Thread_flag=_THREAD_REDUCE;
            pthread_mutex_unlock(&tp->var_lock);
            for(int i=0;i<_THREAD_REDUCE;i++)
            {
                pthread_cond_signal(&tp->Not_Empty);
            }
            //printf("Manager Thread 0x%x,Delete Old Thread Successfully..\n",(unsigned int)pthread_self());
        }
        usleep(100);
    }
    return NULL;
}

void TcpNet::Accept_business(int serverfd)
{
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    addrlen=sizeof(clientaddr);
    int clientfd;
    while((clientfd=accept(serverfd,(struct sockaddr*)&clientaddr,&addrlen))>0)
    {
        char IP[16];
        bzero(IP,16);
        inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,IP,sizeof(IP));
        int value = 1;
        setsockopt(clientfd, IPPROTO_TCP, TCP_NODELAY ,(char *)&value, sizeof(int));
        printf("[%s] [%d] Connected successfully\n",IP,ntohs(clientaddr.sin_port));
        sockset.insert(clientfd);
        //cout<<"clientfd"<<clientfd<<" ADD LISTEN"<<endl;
        struct epoll_event node;
        node.data.fd=clientfd;
        node.events=EPOLLIN|EPOLLONESHOT;
        if((epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&node))==-1)
        {
            printf("add epfd failed\n");
            exit(0);
        }
    }
}

void *Forward_business(void *arg)
{
    forward_t ft=*(forward_t*)arg;
    if (!ft.clientfd || -1 == ft.clientfd)
        {
            cout << "TcpNet::RecvData sock error" << endl;
            return NULL;
        }
        //2.接收数据
        int nRecvNum = 0;
        int nPackSize = 0;
        //使用偏移量，记录累计读取了多少数据
        int offset = 0;
        //接收包长度,包长度放在nPackSize中
        nRecvNum = recv(ft.clientfd, (char*)&nPackSize, sizeof(int), 0);
        if (nRecvNum > 0)
        {
            char* recvBuf = new char[nPackSize];
            //接收包内容
            while (nPackSize > 0)
            {
                nRecvNum = recv(ft.clientfd, recvBuf + offset, nPackSize, 0);
                if (nRecvNum > 0)
                {
                    offset += nRecvNum;
                    nPackSize -= nRecvNum;
                }
//                else if(nRecvNum==-1)
//                {
//                    if(errno==EAGAIN)
//                        continue;
//                }
            }
            //发送给中介者类，接收完数据了，就交给核心类去处理数据
            ft.pthis->m_pMediator->AcceptData(recvBuf, offset, ft.clientfd);
            struct epoll_event node;
            node.data.fd=ft.clientfd;
            node.events=EPOLLIN|EPOLLONESHOT;
            if((epoll_ctl(epfd,EPOLL_CTL_MOD,ft.clientfd,&node))==-1)
            {
                printf("add epfd failed\n");
                exit(0);
            }
        }
        else if(nRecvNum==0)
        {
            epoll_ctl(epfd,EPOLL_CTL_DEL,ft.clientfd,NULL);
            close(ft.clientfd);
            return NULL;
        }
        else
        {
            cout << "TcpNet::RecvData error:" << strerror(errno)<< endl;
        }
        return NULL;
}


tp_t* TcpNet::TP_Create()
{
    //1.初始化线程锁
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
    //2.创建线程池类型
    tp=(tp_t*)malloc(sizeof(tp_t));
    //初始化线程资源
    pthread_cond_init(&tp->Not_Full,NULL);
    pthread_cond_init(&tp->Not_Empty,NULL);
    pthread_mutex_init(&tp->queue_lock,NULL);
    pthread_mutex_init(&tp->var_lock,NULL);
    tp->Thread_Max=_TMAX;
    tp->Thread_Min=_TMIN;
    tp->Thread_Shutdown=1;
    tp->Thread_flag=0;
    tp->Thread_Alive=_TMIN;
    tp->Front=0;
    tp->Rear=0;
    tp->Cur=0;
    tp->Max=_CMAX;
    tp->Container=(bs_t*)malloc(sizeof(bs_t)*_CMAX);
    bzero(tp->Container,sizeof(bs_t)*_CMAX);
    tp->cus_tids=(pthread_t*)malloc(sizeof(pthread_t)*_TMAX);
    bzero(tp->cus_tids,sizeof(pthread_t)*_TMAX);
    //预先创建_TMIN个闲置消费者
    int err;
    for(int i=0;i<_TMIN;i++)
    {
        if((err=pthread_create(&tp->cus_tids[i],&thread_attr,TP_Customer,(void*)tp)!=0))
        {
            printf("create customer thread failed:%s\n",strerror(err));
            return 0;
        }
    }
    //预先创建1个管理者线程
    if((pthread_create(&tp->mag_tid,&thread_attr,TP_Manager,(void*)tp))!=0)
    {
        printf("create manager thread failed:%s\n",strerror(err));
        return nullptr;
    }
    return tp;
}

send_poll_t * TcpNet::TP_Send_Create()
{
    //2.创建线程池类型
    send_poll_t *send_tp=(send_poll_t*)malloc(sizeof(send_poll_t));
    //初始化线程资源
    pthread_cond_init(&send_tp->Not_Full,NULL);
    pthread_cond_init(&send_tp->Not_Empty,NULL);
    pthread_mutex_init(&send_tp->queue_lock,NULL);
    send_tp->Thread_Shutdown=1;
    send_tp->Front=0;
    send_tp->Rear=0;
    send_tp->Cur=0;
    send_tp->Max=_CMAX;
    send_tp->Container=(bs_t*)malloc(sizeof(bs_t)*_CMAX);
    bzero(send_tp->Container,sizeof(bs_t)*_CMAX);
    //预先创建1个闲置消费者
    int err;
    if((err=pthread_create(&send_tp->send_tid,&thread_attr,TP_SEND_Customer,(void*)send_tp)!=0))
    {
        printf("create customer thread failed:%s\n",strerror(err));
        return nullptr;
    }
    return send_tp;
}

int TcpNet::TP_Destroy()
{
    //1.释放线程池
    tp->Thread_Shutdown=0;
    free(tp->Container);
    free(tp->cus_tids);
    tp->Container=nullptr;
    tp->cus_tids=nullptr;
    pthread_mutex_destroy(&tp->queue_lock);
    pthread_mutex_destroy(&tp->var_lock);
    pthread_cond_destroy(&tp->Not_Full);
    pthread_cond_destroy(&tp->Not_Empty);
    pthread_attr_destroy(&thread_attr);
    free(tp);
    tp=nullptr;
    //2.释放队列池
    send_tp->Thread_Shutdown=0;
    free(send_tp->Container);
    send_tp->Container=nullptr;
    pthread_mutex_destroy(&send_tp->queue_lock);
    pthread_cond_destroy(&send_tp->Not_Full);
    pthread_cond_destroy(&send_tp->Not_Empty);
    free(send_tp);
    send_tp=nullptr;
    return 0;
}


int TcpNet::TP_Epoll_Create()
{
    //1.创建监听树
    epfd=epoll_create(_EPOLL_MAX);
    //2.加载监听元素
    struct epoll_event node;
    node.data.fd=m_sock;
    node.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,m_sock,&node);
    return 0;
}

int TcpNet::TP_Epoll_Listen()
{
    int readycode=0;
    struct epoll_event nready[_EPOLL_MAX];
    int flag=0;
    while(tp->Thread_Shutdown)
    {
        flag=0;
        readycode=epoll_wait(epfd,nready,_EPOLL_MAX+1,100);
        if(readycode==-1)
        {
            perror("TP_EPOLL_LISTEN,EPOLL WAIT FAILED");
            exit(0);
        }
        while(readycode)
        {
            if(nready[flag].data.fd==m_sock)
            {
                Accept_business(m_sock);
            }
            else
            {
                bs_t bs;
                bs.Business_Addr=Forward_business;
                forward_t ft;
                ft.pthis=this;
                ft.clientfd=nready[flag].data.fd;
                bs.arg=(void*)&ft;
                //printf("Add Forward Business..\n");
                TP_Producer(bs,tp);
            }
            readycode--;
            flag++;
        }
    }
    return 0;
}

int TcpNet::TP_Producer(bs_t business,tp_t*tp)
{
    if(tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&tp->queue_lock);
        while(tp->Cur==tp->Max)
        {
            pthread_cond_wait(&tp->Not_Full,&tp->queue_lock);
        }
        if(tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&tp->queue_lock);
            printf("Producer thread shutdown\n");
            return -1;
        }
        tp->Container[tp->Front].Business_Addr=business.Business_Addr;
        tp->Container[tp->Front].arg=business.arg;
        tp->Front=(tp->Front+1)%tp->Max;
        tp->Cur++;
        //释放锁
        pthread_cond_signal(&tp->Not_Empty);
        pthread_mutex_unlock(&tp->queue_lock);
    }
    return 0;
}

int TcpNet::TP_Producer(bs_t business, send_poll_t *send_tp)
{
    if(send_tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&send_tp->queue_lock);
        while(send_tp->Cur==send_tp->Max)
        {
            pthread_cond_wait(&send_tp->Not_Full,&send_tp->queue_lock);
        }
        if(send_tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&send_tp->queue_lock);
            printf("Producer thread shutdown\n");
            return -1;
        }
        send_tp->Container[send_tp->Front].Business_Addr=business.Business_Addr;
        send_tp->Container[send_tp->Front].arg=business.arg;
        send_tp->Front=(send_tp->Front+1)%send_tp->Max;
        send_tp->Cur++;
        //释放锁
        pthread_cond_signal(&send_tp->Not_Empty);
        pthread_mutex_unlock(&send_tp->queue_lock);
    }
    return 0;
}



=======
#include"TcpNet.h"
#include"../Mediator/TcpMediator.h"
//设置分离态线程属性
static int epfd;
static pthread_attr_t thread_attr;
#define TEST

//构造
TcpNet::TcpNet(INetMediator* m_p):m_sock(-1),m_isStop(false),tp(nullptr),send_tp(nullptr)
{
	m_pMediator = m_p;
}
//析构
TcpNet::~TcpNet()
{
    TP_Destroy();
    UinitNet();
}
//初始化网络
bool TcpNet::InitNet()
{
    //2.创建套接字
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock == -1)
    {
        cout << "socket error:" << strerror(errno) << endl;
        return false;
    }
    else
    {
        cout << "create socket successfully" << endl;
    }
    //设置非阻塞
    setNonBlockFd(m_sock);
    setRecvBufSize(m_sock);
    setSendBufSize(m_sock);
    setNoDelay(m_sock);

    //3.分配IP地址
    struct sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(TCP_PORT);
    addrServer.sin_addr.s_addr = INADDR_ANY;
    //4.端口服用
#ifdef TEST
    int value = 1;
    setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR ,(char *)&value, sizeof(int));
#endif
    int err;
    err = bind(m_sock, (sockaddr*)&addrServer, sizeof(addrServer));
    if (err !=0)
    {
        cout << "bind error:" <<strerror(errno) << endl;
        return false;
    }
    else
    {
        cout << "bind socket successfully" << endl;
    }
    //4.监听
    listen(m_sock, BACK_LOG);
    if (err == -1)
    {
        cout << "listen error:" << strerror(errno)<< endl;
        return false;
    }
    else
    {
        cout << "listen successfully" << endl;
    }
    //5.创建接受线程池+发送线程池
    if(((tp=TP_Create())==nullptr)||((send_tp=TP_Send_Create())==nullptr))
    {
        return false;
    }
    return true;
  
}
//卸载网络
void TcpNet::UinitNet()
{
    for(auto ite=sockset.begin();ite!=sockset.end();)
    {
        close(*ite);
        ite=sockset.erase(ite);
    }
    m_isStop = true;
    if (m_sock && m_sock != -1)
    {
        close(m_sock);
    }
}

//接收数据
void TcpNet::AcceptData()
{
}

void TcpNet::Eventloop()
{
    //建立epoll
    TP_Epoll_Create();
    //加载监听
    TP_Epoll_Listen();
    //监听到位后，进行业务处理
}

void *MySendData(void *arg)
{
    send_t *st=(send_t*)arg;
    //1.校验参数
    if (!st->buf || st->len <= 0)
    {
        cout << "TcpNet::SendData error" << endl;
        return NULL;
    }
    //2.将包长度和包内容一起打包发送
    char* pbuf = new char[st->len+4];
    memset(pbuf, 0, st->len + 4);
    //写入包大小
    int* plen = reinterpret_cast<int*>(pbuf);
    *plen = st->len;
    //写入包内容
    char* ppbuf = pbuf;
    ppbuf += 4;
    memcpy(ppbuf, st->buf, st->len);
    //发送数据包
    if (send(st->sock, pbuf, st->len + 4, 0) <= 0)
    {
        cout << "TcpNet::SendData error:" << strerror(errno) << endl;
        delete[]pbuf;
        pbuf=nullptr;
    }
    delete st;
    st=nullptr;
    return NULL;
}
//发送数据
bool TcpNet::SendData(char*buf,int len,long Ip)
{
    bs_t bs;
    send_t* st=(send_t*)malloc(sizeof(send_t));
    if(len>TCP_RECVBUF)
    {
        printf("send error: send len out of range\n");
        return false;
    }
    memcpy(st->buf,buf,len);
    st->len=len;
    st->sock=Ip;
    bs.Business_Addr=MySendData;
    bs.arg=(void*)st;
    TP_Producer(bs,send_tp);
    return true;
}
void* TcpNet::TP_Customer(void *arg)
{
    tp_t*tp=(tp_t*)arg;
    while(tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&tp->queue_lock);
        while (tp->Cur==0) {
            pthread_cond_wait(&tp->Not_Empty,&tp->queue_lock);
            pthread_mutex_lock(&tp->var_lock);
            if(tp->Thread_flag>0)
            {
                pthread_mutex_unlock(&tp->queue_lock);
                tp->Thread_flag--;
                tp->Thread_Alive--;
                //printf("pthread 0x%x exit... thread_flag:%d \n ",(unsigned int)pthread_self(),tp->Thread_flag);
                pthread_mutex_unlock(&tp->var_lock);
                pthread_exit(NULL);
            }
            pthread_mutex_unlock(&tp->var_lock);
        }
        if(tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&tp->queue_lock);
            printf("TP_Customer Thread_Shutdown error\n");
            break;
        }
        //printf("Get Work,0x%x is Working\n",(unsigned int)pthread_self());
        bs_t bs;
        bs.Business_Addr=tp->Container[tp->Rear].Business_Addr;
        bs.arg=tp->Container[tp->Rear].arg;
        tp->Cur--;
        tp->Rear=(tp->Rear+1)%tp->Max;
        pthread_cond_signal(&tp->Not_Full);
        pthread_mutex_unlock(&tp->queue_lock);
        pthread_mutex_lock(&tp->var_lock);
        tp->Thread_Busy++;
        tp->Thread_Alive--;
        pthread_mutex_unlock(&tp->var_lock);
        bs.Business_Addr(bs.arg);
        pthread_mutex_lock(&tp->var_lock);
        tp->Thread_Busy--;
        tp->Thread_Alive++;
        pthread_mutex_unlock(&tp->var_lock);
    }
    printf("Customer Thread 0x%x Shutdown \n",(unsigned int)pthread_self());
    pthread_exit(NULL);
}

void *TcpNet::TP_SEND_Customer(void *arg)
{
    send_poll_t *send_tp=(send_poll_t*)arg;
    while(send_tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&send_tp->queue_lock);
        while (send_tp->Cur==0) {
            pthread_cond_wait(&send_tp->Not_Empty,&send_tp->queue_lock);
        }
        if(send_tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&send_tp->queue_lock);
            printf("TP_SEND_Customer Thread_Shutdown error\n");
            break;
        }
        printf("Send Work,0x%x is Working\n",(unsigned int)pthread_self());
        bs_t bs;
        bs.Business_Addr=send_tp->Container[send_tp->Rear].Business_Addr;
        bs.arg=send_tp->Container[send_tp->Rear].arg;
        send_tp->Cur--;
        send_tp->Rear=(send_tp->Rear+1)%send_tp->Max;
        pthread_cond_signal(&send_tp->Not_Full);
        pthread_mutex_unlock(&send_tp->queue_lock);
        bs.Business_Addr(bs.arg);
    }
    printf("SEND_Customer Thread 0x%x Shutdown \n",(unsigned int)pthread_self());
    pthread_exit(NULL);
}
int IF_THREAD_ALIVE(pthread_t tid)
{
    int err;
    if((err=pthread_kill(tid,0))==ESRCH)
    {
        return 0;
    }
    return 1;
}
void* TcpNet::TP_Manager(void *arg)
{
    tp_t*tp=(tp_t*)arg;
    double state;
    int addflag;
    int alive;
    int busy;
    int flag;
    int Max;
    int Min;
    int add;
    int Cur;
    int Thread_Cur=0;
    while(tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&tp->var_lock);
        alive=tp->Thread_Alive;
        busy=tp->Thread_Busy;
        flag=tp->Thread_flag;
        Max=tp->Thread_Max;
        Min=tp->Thread_Min;
        Cur=tp->Cur;
        pthread_mutex_unlock(&tp->var_lock);
        state=(double)busy/(alive+busy)*100;
        Thread_Cur=alive+busy;
        //printf("Busy Thread Number:%d,Alive Thread Number:%d,State:%2.lf\n",busy,alive,state);
        while(flag)
        {
            pthread_mutex_lock(&tp->var_lock);
            flag=tp->Thread_flag;
            pthread_mutex_unlock(&tp->var_lock);
            //printf("Wait For Thread Exit,Flag %d\n",flag);
            sleep(1);
        }
        //如果大于70就扩容
        if(state>=70&&(Thread_Cur+_INCREASE_THREAD)<Max)
        {
            //printf("Increase Thread Number\n");
            for(addflag=0, add=0;addflag<tp->Thread_Max&&add<_INCREASE_THREAD;addflag++)
            {
                if(tp->cus_tids[addflag]==0||(IF_THREAD_ALIVE(tp->cus_tids[addflag])!=0))
                {
                    int err;
                    if((err=pthread_create(&tp->cus_tids[addflag],&thread_attr,TP_Customer,(void*)tp))>0)
                    {
                            printf("TP_Manager,Create Customer Thread Failed%s\n",strerror(err));
                            exit(0);
                    }
                    add++;
                    pthread_mutex_lock(&tp->var_lock);
                    tp->Thread_Alive++;
                    pthread_mutex_unlock(&tp->var_lock);
                }
            }
           //printf("Manager Thread 0x%x,Create New Thread Successfully..\n",(unsigned int)pthread_self());
        }
        //如果闲置线程大于2倍就缩减，或者闲置占比比较高就缩减
        if(state<=20&&Thread_Cur-_THREAD_REDUCE>=Min)
        {
            pthread_mutex_lock(&tp->var_lock);
            tp->Thread_flag=_THREAD_REDUCE;
            pthread_mutex_unlock(&tp->var_lock);
            for(int i=0;i<_THREAD_REDUCE;i++)
            {
                pthread_cond_signal(&tp->Not_Empty);
            }
            //printf("Manager Thread 0x%x,Delete Old Thread Successfully..\n",(unsigned int)pthread_self());
        }
        usleep(100);
    }
    return NULL;
}

void TcpNet::Accept_business(int serverfd)
{
    struct sockaddr_in clientaddr;
    socklen_t addrlen;
    addrlen=sizeof(clientaddr);
    int clientfd;
    while((clientfd=accept(serverfd,(struct sockaddr*)&clientaddr,&addrlen))>0)
    {
        char IP[16];
        bzero(IP,16);
        inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,IP,sizeof(IP));
        int value = 1;
        setsockopt(clientfd, IPPROTO_TCP, TCP_NODELAY ,(char *)&value, sizeof(int));
        printf("[%s] [%d] Connected successfully\n",IP,ntohs(clientaddr.sin_port));
        sockset.insert(clientfd);
        //cout<<"clientfd"<<clientfd<<" ADD LISTEN"<<endl;
        struct epoll_event node;
        node.data.fd=clientfd;
        node.events=EPOLLIN|EPOLLONESHOT;
        if((epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&node))==-1)
        {
            printf("add epfd failed\n");
            exit(0);
        }
    }
}

void *Forward_business(void *arg)
{
    forward_t ft=*(forward_t*)arg;
    if (!ft.clientfd || -1 == ft.clientfd)
        {
            cout << "TcpNet::RecvData sock error" << endl;
            return NULL;
        }
        //2.接收数据
        int nRecvNum = 0;
        int nPackSize = 0;
        //使用偏移量，记录累计读取了多少数据
        int offset = 0;
        //接收包长度,包长度放在nPackSize中
        nRecvNum = recv(ft.clientfd, (char*)&nPackSize, sizeof(int), 0);
        if (nRecvNum > 0)
        {
            char* recvBuf = new char[nPackSize];
            //接收包内容
            while (nPackSize > 0)
            {
                nRecvNum = recv(ft.clientfd, recvBuf + offset, nPackSize, 0);
                if (nRecvNum > 0)
                {
                    offset += nRecvNum;
                    nPackSize -= nRecvNum;
                }
//                else if(nRecvNum==-1)
//                {
//                    if(errno==EAGAIN)
//                        continue;
//                }
            }
            //发送给中介者类，接收完数据了，就交给核心类去处理数据
            ft.pthis->m_pMediator->AcceptData(recvBuf, offset, ft.clientfd);
            struct epoll_event node;
            node.data.fd=ft.clientfd;
            node.events=EPOLLIN|EPOLLONESHOT;
            if((epoll_ctl(epfd,EPOLL_CTL_MOD,ft.clientfd,&node))==-1)
            {
                printf("add epfd failed\n");
                exit(0);
            }
        }
        else if(nRecvNum==0)
        {
            epoll_ctl(epfd,EPOLL_CTL_DEL,ft.clientfd,NULL);
            close(ft.clientfd);
            return NULL;
        }
        else
        {
            cout << "TcpNet::RecvData error:" << strerror(errno)<< endl;
        }
        return NULL;
}


tp_t* TcpNet::TP_Create()
{
    //1.初始化线程锁
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
    //2.创建线程池类型
    tp=(tp_t*)malloc(sizeof(tp_t));
    //初始化线程资源
    pthread_cond_init(&tp->Not_Full,NULL);
    pthread_cond_init(&tp->Not_Empty,NULL);
    pthread_mutex_init(&tp->queue_lock,NULL);
    pthread_mutex_init(&tp->var_lock,NULL);
    tp->Thread_Max=_TMAX;
    tp->Thread_Min=_TMIN;
    tp->Thread_Shutdown=1;
    tp->Thread_flag=0;
    tp->Thread_Alive=_TMIN;
    tp->Front=0;
    tp->Rear=0;
    tp->Cur=0;
    tp->Max=_CMAX;
    tp->Container=(bs_t*)malloc(sizeof(bs_t)*_CMAX);
    bzero(tp->Container,sizeof(bs_t)*_CMAX);
    tp->cus_tids=(pthread_t*)malloc(sizeof(pthread_t)*_TMAX);
    bzero(tp->cus_tids,sizeof(pthread_t)*_TMAX);
    //预先创建_TMIN个闲置消费者
    int err;
    for(int i=0;i<_TMIN;i++)
    {
        if((err=pthread_create(&tp->cus_tids[i],&thread_attr,TP_Customer,(void*)tp)!=0))
        {
            printf("create customer thread failed:%s\n",strerror(err));
            return 0;
        }
    }
    //预先创建1个管理者线程
    if((pthread_create(&tp->mag_tid,&thread_attr,TP_Manager,(void*)tp))!=0)
    {
        printf("create manager thread failed:%s\n",strerror(err));
        return nullptr;
    }
    return tp;
}

send_poll_t * TcpNet::TP_Send_Create()
{
    //2.创建线程池类型
    send_poll_t *send_tp=(send_poll_t*)malloc(sizeof(send_poll_t));
    //初始化线程资源
    pthread_cond_init(&send_tp->Not_Full,NULL);
    pthread_cond_init(&send_tp->Not_Empty,NULL);
    pthread_mutex_init(&send_tp->queue_lock,NULL);
    send_tp->Thread_Shutdown=1;
    send_tp->Front=0;
    send_tp->Rear=0;
    send_tp->Cur=0;
    send_tp->Max=_CMAX;
    send_tp->Container=(bs_t*)malloc(sizeof(bs_t)*_CMAX);
    bzero(send_tp->Container,sizeof(bs_t)*_CMAX);
    //预先创建1个闲置消费者
    int err;
    if((err=pthread_create(&send_tp->send_tid,&thread_attr,TP_SEND_Customer,(void*)send_tp)!=0))
    {
        printf("create customer thread failed:%s\n",strerror(err));
        return nullptr;
    }
    return send_tp;
}

int TcpNet::TP_Destroy()
{
    //1.释放线程池
    tp->Thread_Shutdown=0;
    free(tp->Container);
    free(tp->cus_tids);
    tp->Container=nullptr;
    tp->cus_tids=nullptr;
    pthread_mutex_destroy(&tp->queue_lock);
    pthread_mutex_destroy(&tp->var_lock);
    pthread_cond_destroy(&tp->Not_Full);
    pthread_cond_destroy(&tp->Not_Empty);
    pthread_attr_destroy(&thread_attr);
    free(tp);
    tp=nullptr;
    //2.释放队列池
    send_tp->Thread_Shutdown=0;
    free(send_tp->Container);
    send_tp->Container=nullptr;
    pthread_mutex_destroy(&send_tp->queue_lock);
    pthread_cond_destroy(&send_tp->Not_Full);
    pthread_cond_destroy(&send_tp->Not_Empty);
    free(send_tp);
    send_tp=nullptr;
    return 0;
}


int TcpNet::TP_Epoll_Create()
{
    //1.创建监听树
    epfd=epoll_create(_EPOLL_MAX);
    //2.加载监听元素
    struct epoll_event node;
    node.data.fd=m_sock;
    node.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,m_sock,&node);
    return 0;
}

int TcpNet::TP_Epoll_Listen()
{
    int readycode=0;
    struct epoll_event nready[_EPOLL_MAX];
    int flag=0;
    while(tp->Thread_Shutdown)
    {
        flag=0;
        readycode=epoll_wait(epfd,nready,_EPOLL_MAX+1,100);
        if(readycode==-1)
        {
            perror("TP_EPOLL_LISTEN,EPOLL WAIT FAILED");
            exit(0);
        }
        while(readycode)
        {
            if(nready[flag].data.fd==m_sock)
            {
                Accept_business(m_sock);
            }
            else
            {
                bs_t bs;
                bs.Business_Addr=Forward_business;
                forward_t ft;
                ft.pthis=this;
                ft.clientfd=nready[flag].data.fd;
                bs.arg=(void*)&ft;
                //printf("Add Forward Business..\n");
                TP_Producer(bs,tp);
            }
            readycode--;
            flag++;
        }
    }
    return 0;
}

int TcpNet::TP_Producer(bs_t business,tp_t*tp)
{
    if(tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&tp->queue_lock);
        while(tp->Cur==tp->Max)
        {
            pthread_cond_wait(&tp->Not_Full,&tp->queue_lock);
        }
        if(tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&tp->queue_lock);
            printf("Producer thread shutdown\n");
            return -1;
        }
        tp->Container[tp->Front].Business_Addr=business.Business_Addr;
        tp->Container[tp->Front].arg=business.arg;
        tp->Front=(tp->Front+1)%tp->Max;
        tp->Cur++;
        //释放锁
        pthread_cond_signal(&tp->Not_Empty);
        pthread_mutex_unlock(&tp->queue_lock);
    }
    return 0;
}

int TcpNet::TP_Producer(bs_t business, send_poll_t *send_tp)
{
    if(send_tp->Thread_Shutdown)
    {
        pthread_mutex_lock(&send_tp->queue_lock);
        while(send_tp->Cur==send_tp->Max)
        {
            pthread_cond_wait(&send_tp->Not_Full,&send_tp->queue_lock);
        }
        if(send_tp->Thread_Shutdown!=1)
        {
            pthread_mutex_unlock(&send_tp->queue_lock);
            printf("Producer thread shutdown\n");
            return -1;
        }
        send_tp->Container[send_tp->Front].Business_Addr=business.Business_Addr;
        send_tp->Container[send_tp->Front].arg=business.arg;
        send_tp->Front=(send_tp->Front+1)%send_tp->Max;
        send_tp->Cur++;
        //释放锁
        pthread_cond_signal(&send_tp->Not_Empty);
        pthread_mutex_unlock(&send_tp->queue_lock);
    }
    return 0;
}

void TcpNet::setNonBlockFd(int fd)
{
    int flags = 0;
    flags = fcntl(fd, F_GETFL, 0);
    int ret = fcntl(fd, F_SETFL, flags|O_NONBLOCK);
    if( ret == -1)
        perror("setNonBlockFd fail:");
}

void TcpNet::setRecvBufSize( int fd)
{
    //接收缓冲区
    int nRecvBuf = 256*1024;//设置为 256 K
    setsockopt(fd,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
}

void TcpNet::setSendBufSize( int fd)
{
    //发送缓冲区
    int nSendBuf=128*1024;//设置为 128 K
    setsockopt(fd,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
}

#include<netinet/tcp.h>
void TcpNet::setNoDelay( int fd)
{
    //nodelay
    int value = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY ,(char *)&value, sizeof(int));
}



>>>>>>> bbdc256 (version and audio)
