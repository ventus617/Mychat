#include "ckernel.h"
#include<QMessageBox>
#include<QTextCodec>
#include<QInputDialog>
#include<QTime>

#define TypeBase(type) ((type)-TCP_TYPE_HEAD-10)
#define NetProtocolMap(type) m_netProtocalMap[TypeBase(type)]

ckernel::ckernel(QObject *parent) : QObject(parent),m_pMediator(nullptr),m_Id(0),m_name("")
{
    qDebug()<<__func__;
    //1.初始化数组
    setProtocolMap();
    //注册&登录窗口new对象
    m_pMyLogInDlg=new logindialog;
    m_pMyLogInDlg->showNormal();
    //绑定发送注册的槽函数
    connect(m_pMyLogInDlg,SIGNAL(SIG_registerCommit(QString,QString,QString )),
            this,SLOT(slot_registerCommit(QString, QString , QString )));
    //绑定发送登录界面的槽函数
    connect(m_pMyLogInDlg,SIGNAL(SIG_LogCommit(QString ,QString )),
            this,SLOT(slot_LogInCommit(QString , QString )));
    //绑定关闭登录和注册界面的槽函数
    connect(m_pMyLogInDlg,SIGNAL(SIG_closeLog()),this,SLOT(slot_closeLogInDlg()));
    //给好友列表窗口new对象
    m_pMyUI=new myUI;
    //绑定添加好友的信号和槽函数
    connect(m_pMyUI,SIGNAL(SIG_addFriend()),this,SLOT(slot_addFriend()));
    //绑定关闭好友列表界面的信号和槽函数
    connect(m_pMyUI,SIGNAL(SIG_closeMyChatDlg()),this,SLOT(slot_closeMyUIDlg()));
    //给好友选择窗口new对象
    m_select= new ourchatselect;
    connect(m_select,SIGNAL(SIG_SendSelect(QSet<int>*)),this,SLOT(slot_selectFriend(QSet<int>* )));
    //给中介者类new对象
    m_pMediator=new TcpClientMediator; 
    //打开网络
    if(!m_pMediator->OpenNet())
    {
        QMessageBox::about(m_pMyLogInDlg,"提示","打开网络失败");
        exit(0);
    }
    //绑定发送所有数据信号和槽函数
    connect(m_pMediator,SIGNAL(SIG_readData(char*,int,long)),this,SLOT(slot_readyData(char *, int , long )));
}

ckernel::~ckernel()
{
    qDebug()<<__func__;
    //1.回收资源
    if(m_pMyUI)
    {
        m_pMyUI->hide();
        delete m_pMyUI;
        m_pMyUI=nullptr;
    }
    if(m_pMyLogInDlg)
    {
        m_pMyLogInDlg->hide();
        delete m_pMyLogInDlg;
        m_pMyLogInDlg=nullptr;
    }
    if(m_select)
    {
        m_select->hide();
        delete m_select;
        m_select=nullptr;
    }
    if(m_pMediator)
    {
        m_pMediator->CloseNet();
        delete m_pMediator;
        m_pMediator=nullptr;
    }

}

void ckernel::setProtocolMap()
{
    qDebug()<<__func__;
    memset(m_netProtocalMap, 0, TCP_PROTOCAL_COUNT * sizeof(pfun));
    NetProtocolMap(TCP_REGISTER_RS) = &ckernel::dealRegisterRS;
    NetProtocolMap(TCP_LOGIN_RS) = &ckernel::dealLogInRS;
    NetProtocolMap(TCP_ADD_RQ) = &ckernel::dealAddRQ;
    NetProtocolMap(TCP_ADD_RS) = &ckernel::dealAddRS;
    NetProtocolMap(TCP_OFFLINE_RQ) = &ckernel::dealOfflineRQ;
    NetProtocolMap(TCP_CHAT_RQ) = &ckernel::dealChatRQ;
    NetProtocolMap(TCP_CHAT_RS) = &ckernel::dealChatRS;
    NetProtocolMap(TCP_INFO) = &ckernel::dealFriendInfo;
    NetProtocolMap(TCP_OUR_INFO)=&ckernel::dealOurChatFriendInfo;
    NetProtocolMap(TCP_OURCHAT_TALK_RQ)=&ckernel::dealOurChatTalk;
    NetProtocolMap(TCP_OURCHAT_RS)=&ckernel::dealOurChatRS;
    NetProtocolMap(TCP_FILE_RQ)=&ckernel::dealFileBlockRQ;
    NetProtocolMap(TCP_FILE_RS)=&ckernel::dealFileBlockRS;
    NetProtocolMap(TCP_SEND_FILE_RQ)=&ckernel::dealFileInfoRQ;
    NetProtocolMap(TCP_SEND_FILE_RS)=&ckernel::dealFileInfoRS;
}

void ckernel::dealRegisterRS(char *buf, int nLen, long Ip)
{
    qDebug()<<__func__;
    //1.拆包
    STRU_REGISTER_RS*rs=(STRU_REGISTER_RS*)buf;
    //2.根据注册结果提示用户
    switch(rs->result)
    {
    case register_success :
    {
        QMessageBox::about(m_pMyLogInDlg, "提示", "注册成功");
        break;
    }
    case tel_has_existed :
    {
        QMessageBox::about(m_pMyLogInDlg, "提示", "注册失败，电话号码已被注册");
        break;
    }
    case user_is_existed :
    {
        QMessageBox::about(m_pMyLogInDlg, "提示", "注册失败，昵称已被使用");
        break;
    }
    default:
        break;
    }

}

void ckernel::dealLogInRS(char *buf, int nLen, long Ip)
{
    qDebug() << __func__;
    // 1、拆包
    STRU_LOGIN_RS* rs = (STRU_LOGIN_RS*)buf;

    // 2、根据注册结果提示用户
    switch (rs->result)
    {
    case login_success :
    {
        // 登录成功，隐藏登录界面，显示好友列表界面
        m_pMyLogInDlg->hide();
        m_pMyUI->showNormal();
        // 保存自己的ID
        m_Id = rs->UserId;
        break;
    }
    case user_not_exist :
    {
        QMessageBox::about(m_pMyLogInDlg, "提示", "登录失败，用户不存在");
        break;
    }
    case password_error :
    {
        QMessageBox::about(m_pMyLogInDlg, "提示", "登录失败，密码错误");
        break;
    }
    default:
        break;
    }
}

void ckernel::dealFriendInfo(char *buf, int nLen, long Ip)
{
    qDebug()<<__func__;
    //1.拆包
    STRU_TCP_INFO* info=(STRU_TCP_INFO*)buf;
    //2.编码转换
    QString name=(info->name);
    QString lable=(info->lable);


    //2.判断是不是自己
    if(info->UserId==m_Id)
    {
        //3.是自己的，就设置在界面上方
        m_pMyUI->setInfo(name,lable,info->IconId);
        m_name=name;//存储自己的姓名
        return;
    }

    //3.如果是好友的，判断好友是不是已经在列表上了
    if(m_mapIdToUserinfo.count(info->UserId)==0)//不在列表
    {

        //4.没有就new一个
        userinfo* item=new userinfo;
        //5.给UI窗口设置属性
        item->setInfo(name,lable,info->IconId,info->status,info->UserId);
        //6.把UI窗口添加到列表上
        m_pMyUI->addFriend(item);
        //7.把UI窗口放入map保存起来，key是好友的ID
        m_mapIdToUserinfo[info->UserId]=item;
        //8.绑定槽函数
        connect(item,SIGNAL(SIG_showChatDlg(int)),this,SLOT(slot_showChatDlg(int)));
        //9.new一个与该好友的聊天窗口
        chatdialog* chat=new chatdialog;
        //10.设置属性
        chat->setWindowInfo(name,info->UserId);
        //11.将聊天窗口保存起来,用好友的id存储
        m_mapIDToChatdlg[info->UserId]=chat;
        //12.绑定发送聊天内容的槽函数
        connect(chat,SIGNAL(SIG_SendMsg(int ,QString )),this,SLOT(slot_sendMsg(int , QString )));
        //13.绑定接收选择好友
        connect(chat,SIGNAL(SIG_getSelect()),this,SLOT(slot_ShowSelect()));
        //14.绑定发送文件
        connect(chat,SIGNAL(SIG_SendFile(int ,QString )),this,SLOT(slot_send_file (int ,QString )));
        //15.暂停文件传输
        connect(chat,SIGNAL(SIG_pauseFile(int)),this,SLOT(slot_pause_file(int)));
        //添加好友信息到select组件中
        friendselect* select=new friendselect;
        //设置属性
        select->setinfo(info->UserId,(info->name));
        //连接槽函数
        connect(select,SIGNAL(SIG_CheckFriend(int)),m_select,SLOT(slot_deal_checkBox(int)));
        //添加到m_select控件窗口中
        m_select->addinfo(select);
        //记录窗口
        m_mapIdTOOurSelect[info->UserId]=select;

        return;
    }
    else //在列表,并且好友已经在线
    {
        userinfo* item=m_mapIdToUserinfo[info->UserId];
        item->setInfo(name,lable,info->IconId,info->status,info->UserId);
    }

}

void ckernel::dealChatRS(char *buf, int nLen, long Ip)
{
    qDebug() << __func__;
    STRU_CHAT_RS*rs=(STRU_CHAT_RS*)buf;

    if(m_mapIDToChatdlg.count(rs->frinedId)>0)
    {
        chatdialog* chat=m_mapIDToChatdlg[rs->frinedId];
        chat->IfOffline();
        chat->showNormal();
    }
}

void ckernel::dealChatRQ(char *buf, int nLen, long Ip)
{
    qDebug() << __func__;
    STRU_CHAT_RQ* rq=(STRU_CHAT_RQ*)buf;

    if(m_mapIDToChatdlg.count(rq->userId)>0)
    {
        chatdialog* chat=m_mapIDToChatdlg[rq->userId];
        chat->set_content(rq->content);
        chat->showNormal();
    }
}

void ckernel::dealAddRQ(char *buf, int nLen, long Ip)
{
    qDebug() << __func__;
    // 1、拆包
    STRU_ADD_RQ* rq = (STRU_ADD_RQ*)buf;

    // 2、弹出询问窗口，是否同意添加好友
    STRU_ADD_RS rs;
    QString str = QString("[%1]请求添加你为好友，是否同意？").arg(rq->username);
    if (QMessageBox::Yes == QMessageBox::question(m_pMyUI, "提示", str))
    {
         rs.result= add_friend_success;
    }
    else
    {
        rs.result = user_refuse;
    }
    rs.frinedId = rq->UserId;
    rs.UserId = m_Id;
    strcpy(rs.friendName, rq->friendname);
    // 3、把添加结果返回给服务器
    m_pMediator->SendData((char*)&rs, sizeof (rs),0);
}

void ckernel::dealAddRS(char *buf, int nLen, long Ip)
{
    qDebug() << __func__;
    // 1、拆包
    STRU_ADD_RS* rs = (STRU_ADD_RS*)buf;
    QString friendName = (rs->friendName);

    // 2、根据结果提示用户
    switch (rs->result)
    {
    case add_friend_success:
    {
        QMessageBox::about(m_pMyUI, "提示", QString("添加好友【%1】成功！").arg(friendName));
        break;
    }
    case user_refuse:
    {
        QMessageBox::about(m_pMyUI, "提示", QString("用户【%1】拒绝添加您为好友").arg(friendName));
        break;
    }
    case no_user:
    {
        QMessageBox::about(m_pMyUI, "提示", QString("用户【%1】不存在").arg(friendName));
        break;
    }
    case user_offline:
    {
        QMessageBox::about(m_pMyUI, "提示", QString("用户【%1】不在线").arg(friendName));
        break;
    }
    default:
        break;
    }
}

void ckernel::dealOfflineRQ(char *buf, int nLen, long Ip)
{
    qDebug() << __func__;
    // 1、拆包
    STRU_OFFLINE_RQ* rq = (STRU_OFFLINE_RQ*)buf;

    // 2、找到下线用户的useritem，设置用户下线状态，同时头像变暗
    if (m_mapIdToUserinfo.count(rq->userID) > 0)
    {
        userinfo* item=m_mapIdToUserinfo[rq->userID];
        item->setUseroffline();
    }
}

//群聊创建回复
void ckernel::dealOurChatRS(char *buf, int nLen, long Ip)
{
    qDebug()<<__func__;
    //拆包
    STRU_OURCHAT_RS*rs=(STRU_OURCHAT_RS*)buf;
    switch(rs->result)
    {
    case create_success:
    {
        QMessageBox::about(m_pMyUI,"提示","群聊创建成功");
        break;
    }
    default:
        break;
    }
}

//群聊内的好友信息接收
void ckernel::dealOurChatFriendInfo(char *buf, int nLen, long Ip)
{
    qDebug()<<__func__;
    STRU_TCP_OUR_CHAT_INFO* info=(STRU_TCP_OUR_CHAT_INFO*)buf;
    QString name=(info->name);
    QString lable=(info->lable);
    //1.如果不存在就创建聊天窗口
    if(m_mapIDToOurChatdlg.count(info->OurChatId)==0)
    {
        //给UI添加点击窗口
        Chatuserinfo* item=new Chatuserinfo;
        item->setInfo(QString("群聊%1").arg(info->OurChatId),info->IconId,info->OurChatId);
        connect(item,SIGNAL(SIG_showOurChatDlg(int)),this,SLOT(slot_showOurChatDlg(int)));
        m_mapIdToChatUserinfo[info->OurChatId]=item;
        m_pMyUI->addOurChat(item);
        //2.创建群聊天窗口
        Ourchatdialog* chat=new Ourchatdialog;
        chat->getMyId(info->OurChatId);
        connect(chat,SIGNAL(SIG_Our_SendMsg(int ,QString )),this,SLOT(slot_Our_sendMsg(int , QString )));
        m_mapIDToOurChatdlg[info->OurChatId]=chat;
        //3.将内容输入到组件上
        ourchatuserinfo* friendinfo= new ourchatuserinfo;
        friendinfo->setInfo(name,lable,info->IconId,info->status,info->UserId);
        chat->addMember(friendinfo);
    }
    //存在，就添加好友信息上去即可
    else if(m_mapIDToOurChatdlg.count(info->OurChatId)>0)
    {
        Ourchatdialog* chat=m_mapIDToOurChatdlg[info->OurChatId];
        ourchatuserinfo* friendinfo= new ourchatuserinfo;
        friendinfo->setInfo(name,lable,info->IconId,info->status,info->UserId);
        chat->addMember(friendinfo);
    }

}

//群聊消息的处理
void ckernel::dealOurChatTalk(char *buf, int nLen, long Ip)
{
    qDebug() << __func__;
    STRU_OURCHAT_TALK_RQ* rq=(STRU_OURCHAT_TALK_RQ*)buf;
    QString name=(rq->name);
    QString content=(rq->content);
    if(m_mapIDToOurChatdlg.count(rq->OurChatId)>0&&rq->userId!=m_Id)
    {
        Ourchatdialog* chat=m_mapIDToOurChatdlg[rq->OurChatId];
        chat->set_content(content,name);
        chat->showNormal();
    }
}

void ckernel::dealFileInfoRQ(char *buf, int nLen, long IP)
{
    qDebug()<<__func__;
    STRU_SEND_FILE_RQ*rq=(STRU_SEND_FILE_RQ*)buf;
    qDebug()<<rq->size;
    m_mapIdToFileName[rq->userid]=rq->FileID;
    //找到聊天框
    chatdialog* chat=m_mapIDToChatdlg[rq->userid];
    STRU_SEND_FILE_RS rs;
    rs.userid=m_Id;
    rs.friendid=rq->userid;
    userinfo* item=m_mapIdToUserinfo[rq->userid];
    strcpy(rs.friend_name,item->getMyName().toStdString().c_str());
    //utf8ToGb2312(item->getMyName(),rs.friend_name,sizeof(rs.friend_name));
    chat->showNormal();
    if(QMessageBox::Yes == QMessageBox::question(chat, "提示", "是否确定接收文件?"))
    {
        rs.result=accept_file;
        //选择路径
        selectDir=QFileDialog::getExistingDirectory();
        qDebug()<<selectDir;
    }
    else
    {
        rs.result=refuse_file;
    }
    m_pMediator->SendData((char*)&rs,sizeof(rs),0);
}

void ckernel::dealFileInfoRS(char *buf, int nLen, long IP)
{
    qDebug()<<__func__;
    STRU_SEND_FILE_RS*rs=(STRU_SEND_FILE_RS*)buf;
    chatdialog* chat=m_mapIDToChatdlg[rs->userid];
    userinfo* item=m_mapIdToUserinfo[rs->userid];
    if(rs->result==refuse_file)
    {
        QMessageBox::critical(chat, "错误", QString("对方拒绝接收文件"));
        return;
    }
    else if(rs->result==accept_file)
    {
        STRU_FILE_RQ rq;

        rq.userid=m_Id;
        strcpy(rq.friend_name,item->getMyName().toStdString().c_str());
        //utf8ToGb2312(item->getMyName(),rq.friend_name,sizeof(rq.friend_name));
        //打开文件
        FILE* file=m_mapChatdlgToFile[chat];
        fseek(file,rs->offset,SEEK_SET);
        //根据offset偏移量来偏移发送
        int num=fread(rq.content,1,TCP_CONTENT_SIZE,file);
        rq.offset=rs->offset+num;
        if(m_mapFileToFileSize[m_mapChatdlgToFile[chat]]<=(rs->offset+TCP_CONTENT_SIZE))
        {
            rq.complete=1;
            fclose(file);
        }
        //二进制填满发送
        m_pMediator->SendData((char*)&rq,sizeof(rq),0);
        return;
    }
    else if(rs->result==abrupt_pause)
    {
        QMessageBox::about(chat, "提示", QString("对方暂停接收文件"));
        return;
    }
    else if(rs->result==friend_offline)
    {
         QMessageBox::about(chat, "提示", QString("对方已经离线"));
        if (m_mapIDToChatdlg.count(rs->userid) > 0)
        {
            chat->IfOffline();
            chat->showNormal();
        }
        return;
    }
    else if(rs->result==out_range)
    {
        QMessageBox::about(chat, "提示", QString("您发送的文件超过1Gb"));
        return;
    }
}

void ckernel::dealFileBlockRQ(char *buf, int nLen, long IP)
{
    qDebug()<<__func__;
    STRU_FILE_RQ*rq=(STRU_FILE_RQ*)buf;
    userinfo* item=m_mapIdToUserinfo[rq->userid];
    QString path=selectDir+"/"+m_mapIdToFileName[rq->userid];
    qDebug()<<path;
    chatdialog* chat=m_mapIDToChatdlg[rq->userid];
     FILE* pfile=nullptr;
    if(m_mapChatdlgToAcceptFile.count(chat)==0)
    {
        fopen_s(&pfile, path.toStdString().c_str(), "ab");
        m_mapChatdlgToAcceptFile[chat]=pfile;
    }
    else
    {
       pfile=m_mapChatdlgToAcceptFile[chat];
    }

    if(pfile==nullptr)
    {
         qDebug()<<"pfile error";
        return;
    }
    int num=fwrite(rq->content,1,TCP_CONTENT_SIZE,pfile);

    if(rq->complete!=1)
    {
        //2.写完了回复一个STRU_SEND_FILE_RS
        STRU_SEND_FILE_RS rs;
        rs.offset=rq->offset;
        rs.userid=m_Id;
        rs.result=accept_file;
        strcpy(rs.friend_name,item->getMyName().toStdString().c_str());
        //utf8ToGb2312(item->getMyName(),rs.friend_name,sizeof(rs.friend_name));
        m_pMediator->SendData((char*)&rs,sizeof(rs),0);
        return;
    }
    else
    {
        //3.如果全部写完了回复STRU_FILE_RS
        STRU_FILE_RS rs;
        rs.result=accepted_success;
        rs.userid=m_Id;
        strcpy(rs.friend_name,item->getMyName().toStdString().c_str());
        //utf8ToGb2312(item->getMyName(),rs.friend_name,sizeof(rs.friend_name));
        m_pMediator->SendData((char*)&rs,sizeof(rs),0);
        fwrite("\0",1,1,pfile);
        fclose(pfile);
        auto ite=m_mapChatdlgToAcceptFile.find(chat);
        m_mapChatdlgToAcceptFile.erase(ite);
        ite=nullptr;
        return;
    }
}

void ckernel::dealFileBlockRS(char *buf, int nLen, long IP)
{
    qDebug()<<__func__;
    STRU_FILE_RS*rs=(STRU_FILE_RS*)buf;
    //1.找到聊天框
    chatdialog* chat=m_mapIDToChatdlg[rs->userid];
    //2.显示聊天框
    chat->showNormal();
    if(rs->result==accept_fail)
    {
        QMessageBox::about(chat,"提示","文件接收失败");
    }
    else
    {
        //3.显示文件接受完毕
        QMessageBox::about(chat,"提示","文件接收完毕");
    }
}

void ckernel::utf8ToGb2312(QString utf8, char *gb2312,int len)
{
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    QByteArray ba = gb2312code->fromUnicode(utf8);
    strcpy_s(gb2312, len, ba.data());
}

QString ckernel::gb2312ToUtf8(char *gb2312)
{
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    return gb2312code->toUnicode(gb2312);
}

string ckernel::getMD5(const QString val)
{
    //利用MD5散列函数加密 数据库存相应的散列值(即存储密文即可)
    //可以加盐 加料 来增加安全
    QString str=QString("%1_%2").arg(val).arg(TCP_MD5);
    MD5 md(str.toStdString());
    qDebug()<<str<<" md5: "<<md.toString().c_str();
    return md.toString();
}

void ckernel::slot_readyData(char *buf, int nLen, long IP)
{
    qDebug()<<__func__;
    //1.取出协议头
    PackType type = *(PackType*)buf;
    //2.根据协议头选择对应的函数
    cout << "type:" << type << endl;
    if (TypeBase(type) >= 0 && TypeBase(type) < TCP_PROTOCAL_COUNT)
    {
        //1.按照数组下标取出对应的函数地址
        pfun pf = NetProtocolMap(type);
        if (pf)
        {
            //通过对象去调用普通函数指针
            (this->*pf)(buf, nLen, IP);
        }
        else
        {
            cout << "pf error pf:"<<pf << endl;
        }
    }

    //数据处理完成后清除数据
    delete[]buf;
    buf = nullptr;
}

void ckernel::slot_registerCommit(QString tel, QString name, QString password)
{
    qDebug()<<__func__;
    //1.打包
    STRU_REGISTER_RQ rq;
    strcpy(rq.name,name.toStdString().c_str());
    //utf8ToGb2312(name,rq.name,sizeof(rq.name));
    string pwd_MD5=getMD5(password);
    strcpy(rq.password,pwd_MD5.c_str());
    strcpy(rq.tel,tel.toStdString().c_str());
    //2.发给服务端
    m_pMediator->SendData((char*)&rq,sizeof(rq),0);
}

void ckernel::slot_LogInCommit(QString tel, QString password)
{
    qDebug()<<__func__;
    //打包
    STRU_LOGIN_RQ rq;
    strcpy(rq.tel,tel.toStdString().c_str());
    string pwd_MD5=getMD5(password);
    strcpy(rq.password,pwd_MD5.c_str());

    m_pMediator->SendData((char*)&rq,sizeof(rq),0);
}

void ckernel::slot_sendMsg(int ID, QString content)
{
    qDebug() << __func__;
    STRU_CHAT_RQ rq;
    rq.userId=m_Id;
    rq.friendId=ID;

    strcpy(rq.content,content.toStdString().c_str());

    m_pMediator->SendData((char*)&rq,sizeof(rq),0);

}



void ckernel::slot_showChatDlg(int ID)
{
    qDebug() << __func__;
    if(m_mapIDToChatdlg.count(ID)>0)
    {
        chatdialog*chat =m_mapIDToChatdlg[ID];
        chat->showNormal();
    }
}

void ckernel::slot_showOurChatDlg(int ID)
{
    qDebug() << __func__;
    if(m_mapIDToOurChatdlg.count(ID)>0)
    {
        Ourchatdialog*chat =m_mapIDToOurChatdlg[ID];
        chat->showNormal();
    }
}

void ckernel::slot_addFriend()
{
    qDebug()<<__func__;

    QString name=QInputDialog::getText(m_pMyUI,"添加好友","请输入好友名字");

    //2.校验用户的好友名字
    QString temp_name=name;
    if(name.isEmpty()||temp_name.remove(" ").isEmpty())
    {
        QMessageBox::about(m_pMyUI,"提示","输入昵称不合法");
        return;
    }
    //3.校验用户输入的名字是否是自己的好友的名字
    for(auto ite=m_mapIdToUserinfo.begin();ite!=m_mapIdToUserinfo.end();ite++)
    {
        userinfo* item=*ite;
        if(item->m_name==name)
        {
            QMessageBox::about(m_pMyUI,"提示","该对象已经是您的好友");
            return;
        }
    }
    //4.校验是不是自己
    if(name==m_name)
    {
        QMessageBox::about(m_pMyUI,"提示","添加对象是自己,无法添加");
        return;
    }
    //5.打包请求给服务器
    STRU_ADD_RQ rq;
    rq.UserId=m_Id;
    strcpy(rq.username,m_name.toStdString().c_str());
    strcpy(rq.friendname,name.toStdString().c_str());
    //utf8ToGb2312(name,rq.friendname,sizeof(rq.friendname));
    m_pMediator->SendData((char*)&rq,sizeof(rq),0);
}

void ckernel::slot_closeLogInDlg()
{
    qDebug()<<__func__;
    //1.回收资源
    if(m_pMyUI)
    {
        m_pMyUI->hide();
        delete m_pMyUI;
        m_pMyUI=nullptr;
    }
    if(m_pMyLogInDlg)
    {
        m_pMyLogInDlg->hide();
        delete m_pMyLogInDlg;
        m_pMyLogInDlg=nullptr;
    }
    if(m_select)
    {
        m_select->hide();
        delete m_select;
        m_select=nullptr;
    }
    if(m_pMediator)
    {
        m_pMediator->CloseNet();
        delete m_pMediator;
        m_pMediator=nullptr;
    }

    exit(0);
}

void ckernel::slot_closeMyUIDlg()
{
    qDebug() << __func__;
    STRU_OFFLINE_RQ rq;
    rq.userID=m_Id;
    m_pMediator->SendData((char*)&rq,sizeof(rq),0);

    slot_closeLogInDlg();

    exit(0);
}

void ckernel::slot_deleteFriend()
{

}


void ckernel::slot_ShowSelect()
{
    m_select->showNormal();
}

void ckernel::slot_selectFriend(QSet<int>*set)
{
    //得到好友的id，name 发给服务器端
    STRU_OURCHAT_RQ rq;
    rq.userID=m_Id;
    int size=0;
    for(auto ite=set->begin();ite!=set->end();)
    {
        rq.FriendID[size]=*ite;
        qDebug()<<rq.FriendID[size];
        size++;
        ite=set->erase(ite);
    }
    //rq.FriendID[size]=m_Id;
    m_pMediator->SendData((char*)&rq,sizeof(rq),0);
}

void ckernel::slot_Our_sendMsg(int ID, QString content)
{
    qDebug() << __func__;
    STRU_OURCHAT_TALK_RQ rq;
    rq.userId=m_Id;
    rq.OurChatId=ID;
    strcpy(rq.content,content.toStdString().c_str());
    m_pMediator->SendData((char*)&rq,sizeof(rq),0);
}
// 获取文件名字
void ckernel::GetFileName(char* filename, QString path)
{
    if (path.isEmpty())
    {
        qDebug() << "无效的路径";
        return;
    }

    int pathLen = path.length();
    if (pathLen < 1)
        return;

    QString Name;

    //从后向前找到所传输文件的名称
    int len = 0;
    for (int i = pathLen - 1; path[i] != '/'; i--, len++);
    int j = 0;
    for (int i = pathLen - len; path[i] != '\0'; i++, j++)
    {
        Name[j] = path[i];
    }
    strcpy(filename, Name.toStdString().c_str());
}
void ckernel::slot_send_file(int ID, QString filename)
{
    qDebug() << __func__;
    chatdialog* chat=m_mapIDToChatdlg[ID];
    userinfo* item=m_mapIdToUserinfo[ID];
    // 1、打包
    STRU_SEND_FILE_RQ rq;
    // 2、传文件名
    GetFileName(rq.file_name, filename);
    strcpy(rq.friend_name,item->getMyName().toStdString().c_str());
    //utf8ToGb2312(item->getMyName(),rq.friend_name,sizeof(rq.friend_name));
    qDebug() << "FileName:" << rq.file_name;
    // 3、传文件标识
    QString time = QTime::currentTime().toString("hh_mm_ss");
    QString realname;
    int i;
    for ( i = 0; rq.file_name[i] != '.'; i++)
    {
        realname[i]=rq.file_name[i];
    }
    realname=realname+"_"+time;
    for( i;rq.file_name[i]!='\0';i++)
    {
        realname+=rq.file_name[i];
    }
    qDebug()<<realname;
    strcpy(rq.FileID, realname.toStdString().c_str());
    qDebug() << "FileID:" << rq.FileID;
    // 4、获取文件大小
    FILE* pFile = nullptr;
    fopen_s(&pFile, filename.toStdString().c_str(), "rb");
    if(!pFile) qDebug()<<"ppfile error";
    // 记录文件指针
    m_mapChatdlgToFile[chat]=pFile;
    //从后偏移0个单位开始
    fseek(pFile, 0, SEEK_END);
    rq.size = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);
    qDebug() << "FileSize:" << rq.size;
    // 记录文件大小
    m_mapFileToFileSize[pFile]=rq.size;
    // 6、填写用户自己的ID
    rq.userid=m_Id;
    // 7、发送给服务器
    m_pMediator->SendData((char*)&rq, sizeof (rq),0);
}

void ckernel::slot_pause_file(int ID)
{
    qDebug()<<__func__;
    qDebug()<<ID;
    //发送暂停请求
    userinfo* item=m_mapIdToUserinfo[ID];
    STRU_SEND_FILE_RS rs;
    rs.result=abrupt_pause;
    strcpy(rs.friend_name,item->getMyName().toStdString().c_str());
    //utf8ToGb2312(item->getMyName(),rs.friend_name,sizeof(rs.friend_name));
    m_pMediator->SendData((char*)&rs,sizeof(rs),0);

}



