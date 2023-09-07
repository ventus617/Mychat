#include "kernel.h"
#include "../Mediator/TcpMediator.h"
#include "../md5/md5.h"
#define TypeBase(type) ((type)-TCP_TYPE_HEAD-10)

#define NetProtocolMap(type) m_netProtocolMap[TypeBase(type)]

CKernel* CKernel::pKernel = nullptr;

CKernel::CKernel() :m_pMediator(nullptr)
{
	pKernel = this;
}

CKernel::~CKernel()
{
	closeServer();
}
//1.初始化网络
bool CKernel::startServer()
{
	cout << "CKernel::startServer" << endl;
	//1.初始化协议组
	setProtocolMap();
	//初始化中介者
	m_pMediator = new TcpMediator;
	if (!m_pMediator->OpenNet())
	{
		cout << "打开网络失败" << endl;
		return false;
	}
	//2.连接数据库
	sql.ConnectMySql("127.0.0.1", "root", "z9090900", "myqq");
	return true;
}
//2.关闭网络
void CKernel::closeServer()
{
	cout << "CKernel::closeServer" << endl;
	//回收资源
	if (m_pMediator)
	{
		m_pMediator->CloseNet();
		delete m_pMediator;
		m_pMediator = nullptr;
	}
	sql.DisConnect();
}

//3.处理数据
void CKernel::readyData(char* buf, int len, long Ip)
{
	cout << "CKernel::readyData" << endl;
	//1.取出协议头
	PackType type = *(PackType*)buf;
	//2.根据协议头选择对应的函数
	cout << "type:" << type << endl;
	if (TypeBase(type) >= 0 && TypeBase(type) < TCP_PROTOCAL_COUNT)
	{
		//1.按照数组下标取出对应的函数地址
		pFun pf = NetProtocolMap(type);
		if (pf)
		{
			//通过对象去调用普通函数指针
			(this->*pf)(buf, len, Ip);
		}
		else
		{
			cout << "pf error,pf:"<<pf << endl;
		}
	}

	//数据处理完成后清楚数据
	delete[]buf;
	buf = nullptr;
}

//4.初始化协议组
void CKernel::setProtocolMap()
{
	cout << "CKernel::setProtocolMap" << endl;
	memset(m_netProtocolMap, 0, TCP_PROTOCAL_COUNT * sizeof(pFun));
	NetProtocolMap(TCP_REGISTER_RQ) = &CKernel::dealRegisterRQ;
	NetProtocolMap(TCP_LOGIN_RQ) = &CKernel::dealLogInRQ;
	NetProtocolMap(TCP_ADD_RQ) = &CKernel::dealAddFriendRQ;
	NetProtocolMap(TCP_ADD_RS) = &CKernel::dealAddFriendRS;
	NetProtocolMap(TCP_OFFLINE_RQ) = &CKernel::dealOfflineRQ;
	NetProtocolMap(TCP_CHAT_RQ) = &CKernel::dealChatRQ;
	NetProtocolMap(TCP_OURCHAT_RQ) = &CKernel::dealOurChatRQ;
	NetProtocolMap(TCP_OURCHAT_TALK_RQ)=&CKernel::dealOurChatTalkRQ;
	NetProtocolMap(TCP_FILE_RQ) = &CKernel::dealFileBlockRQ;
	NetProtocolMap(TCP_FILE_RS) = &CKernel::dealFileBlockRS;
	NetProtocolMap(TCP_SEND_FILE_RQ) = &CKernel::dealFileInfoRQ;
	NetProtocolMap(TCP_SEND_FILE_RS) = &CKernel::dealFileInfoRS;
}

//5.注册请求，昵称和电话号码都得unique
void CKernel::dealRegisterRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealRegisterRQ" << endl;
	//1.拆包
	STRU_REGISTER_RQ* rq = (STRU_REGISTER_RQ*)buf;
	//2.校验用户输入的数据是否合法(交给客户端去做)
	//3.检查电话号码是否被注册过，查询数据库
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select tel from t_user where tel='%s';", rq->tel);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}

	STRU_REGISTER_RS rs;
	//4.校验查询的结果
	if (res.size() > 0)
	{
		//5.电话号码被注册过了，返回失败
		rs.result = tel_has_existed;
	}
	else
	{
		//6.电话号码没被注册过，查询昵称
		sprintf_s(sqlBuf, "select name from t_user where name='%s';", rq->name);
		if (!sql.SelectMySql(sqlBuf, 1, res))
		{
			cout << "select mysql error:" << sqlBuf << endl;
			return;
		}
		if (res.size() > 0)
		{
			rs.result = user_is_existed;
		}
		else
		{
			//8.没有注册过昵称，用户数据插入到数据库中
			sprintf_s(sqlBuf, "insert into t_user (name,tel,password) values ('%s','%s','%s')", rq->name, rq->tel, rq->password);
			if (!sql.UpdateMySql(sqlBuf))
			{
				cout << "updata mysql error:" << sqlBuf << endl;
				return;
			}
			//9.返回注册成功
			rs.result = register_success;
		}
	}
	//发送回复包
	m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
}

//6.登录请求
void CKernel::dealLogInRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealLogInRQ" << endl;
	//1.拆包
	STRU_LOGIN_RQ* rq = (STRU_LOGIN_RQ*)buf;
	//2.客户端检查输入合法
	//3.根据tel查password
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id,password from t_user where tel='%s';", rq->tel);
	if (!sql.SelectMySql(sqlBuf, 2, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}

	STRU_LOGIN_RS rs;
	if (res.size() == 0)
	{
		//4.用户不存在
		rs.result = user_not_exist;
	}
	else
	{
		//5.取出id和密码
		int userid = atoi(res.front().c_str());
		res.pop_front();
		
		string password = res.front();
		res.pop_front();

		string pwd_md5;
		pwd_md5 = getMD5(rq->password);
		//6.判断用户输入的密码和存储密码是否一致
		if (pwd_md5!=password)
		{
			rs.result = password_error;
		}
		else
		{
			rs.result = login_success;
			rs.UserId = userid;//告知登录方，自己的id
			
			m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
			
			m_mapIdToSocket[userid] = Ip;

			getUserList(userid);
			//查找自己所在的群
			list<string>res2;
			char sqlBuf2[TCP_SQL_SIZE];
			memset(sqlBuf2, 0, TCP_SQL_SIZE);
			sprintf_s(sqlBuf, "select id_link from t_ourchat where id_user=%d;", userid);
			if (!sql.SelectMySql(sqlBuf, 1, res2))
			{
				cout << "select mysql error:" << sqlBuf << endl;
				return;
			}
			while (res2.size() > 0)
			{
				int ourid = atoi(res2.front().c_str());
				res2.pop_front();
				getOurChatList(ourid, userid);
			}
			return;
		}
	}
	m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
}

//7.查询好友信息
void CKernel::getUserList(int UserId)
{
	cout << "CKernel::getUserList" << endl;
	//1.根据自己的ID查询自己的信息
	STRU_TCP_INFO userInfo;
	getUserInfoByID(UserId,&userInfo);

	//2.把自己的消息返回客户端，客户端解析
	m_pMediator->SendData((char*)&userInfo, sizeof(userInfo), m_mapIdToSocket[UserId]);

	//3.根据自己的ID查询好友列表
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select idB from t_friend where idA=%d;", UserId);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	//4.将多个好友的信息发送给自己
	int friendId;
	STRU_TCP_INFO friendInfo;
	while (res.size() > 0)
	{
		//5.拿到好友的ID
		friendId = atoi(res.front().c_str());
		res.pop_front();

		//6.得到好友的信息
		getUserInfoByID(friendId,&friendInfo);

		//7.发送给客户端
		m_pMediator->SendData((char*)&friendInfo, sizeof(friendInfo), m_mapIdToSocket[UserId]);

		//8.判断好友是否在线
		if (m_mapIdToSocket.count(friendId) > 0)
		{
			//9.告诉好友对方上线了,也就是把自己的信息发给对方即可
			m_pMediator->SendData((char*)&userInfo, sizeof(userInfo), m_mapIdToSocket[friendId]);
		}
	}
}

//8.根据ID查询信息
void CKernel::getUserInfoByID(int Id, STRU_TCP_INFO* info)
{
	cout << "CKernel::getUserInfoByID" << endl;
	//1.根据ID从数据库中查询用户的信息
	//返回一行的每一列内容
	list<string> res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	//使用sprintf，按照格式打印
	sprintf_s(sqlBuf, "select name,lable,iconId from t_user where id= %d;", Id);
	if (!sql.SelectMySql(sqlBuf, 3, res))
	{
		cout << "select from mysql error:" << sqlBuf << endl;
		return;
	}
	//2.获取查询的结果
	if (res.size() == 3)
	{
		strcpy(info->name, res.front().c_str());
		res.pop_front();
		
		strcpy(info->lable, res.front().c_str());
		res.pop_front();

		info->IconId=atoi(res.front().c_str());
		res.pop_front();
	}
	//3.属性赋值
	info->UserId = Id;//id就是传入的id
	if (m_mapIdToSocket.find(Id) != m_mapIdToSocket.end())//如果有socket证明在线
	{
		info->status = status_online;
	}
	else
	{
		info->status = status_offline;
	}
}

//8.根据ID查询信息
void CKernel::getUserInfoByID(int Id, STRU_TCP_OUR_CHAT_INFO* info)
{
	cout << "CKernel::getUserInfoByID" << endl;
	//1.根据ID从数据库中查询用户的信息
	//返回一行的每一列内容
	list<string> res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	//使用sprintf，按照格式打印
	sprintf_s(sqlBuf, "select name,lable,iconId from t_user where id= %d;", Id);
	if (!sql.SelectMySql(sqlBuf, 3, res))
	{
		cout << "select from mysql error:" << sqlBuf << endl;
		return;
	}
	//2.获取查询的结果
	if (res.size() == 3)
	{
		strcpy(info->name, res.front().c_str());
		res.pop_front();

		strcpy(info->lable, res.front().c_str());
		res.pop_front();

		info->IconId = atoi(res.front().c_str());
		res.pop_front();
	}
	//3.属性赋值
	info->UserId = Id;//id就是传入的id
	if (m_mapIdToSocket.find(Id) != m_mapIdToSocket.end())//如果有socket证明在线
	{
		info->status = status_online;
	}
	else
	{
		info->status = status_offline;
	}
}

//9.处理聊天请求
void CKernel::dealChatRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealChatRQ" << endl;
	//1.拆包
	STRU_CHAT_RQ* rq = (STRU_CHAT_RQ*)buf;
	//2.根据好友id查找好友是否在线
	if (m_mapIdToSocket.count(rq->friendId) > 0)
	{
		//3.如果存在，就直接转发
		m_pMediator->SendData(buf, len, m_mapIdToSocket[rq->friendId]);
	}
	else
	{
		//4.如果好友不在线，返回客户端好友不在线
		STRU_CHAT_RS rs;
		rs.result = send_fail;
		rs.frinedId = rq->friendId;
		m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
	}
}

//10.处理添加好友请求
void CKernel::dealAddFriendRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealAddFriendRQ" << endl;
	//1.拆包
	STRU_ADD_RQ* rq = (STRU_ADD_RQ*)buf;
	//2.根据好友昵称查询好友id
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id from t_user where name ='%s';", rq->friendname);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	//3.好友是否存在
	if (res.size() > 0)
	{
		//4.如果好友存在，取出好友id
		int friendID = atoi(res.front().c_str());
		res.pop_front();
		//5.查询是否在线
		if (m_mapIdToSocket.count(friendID) > 0)
		{
			//6.如果好友在线，转发添加好友请求给对方
			m_pMediator->SendData(buf, len, m_mapIdToSocket[friendID]);
		}
		else
		{
			//7.好友不在线，回复好友不在线
			STRU_ADD_RS rs;
			strcpy(rs.friendName, rq->friendname);
			rs.result = user_offline;
			m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
		}
	}
	else
	{
		//8.好友不存在
		STRU_ADD_RS rs;
		strcpy(rs.friendName, rq->friendname);
		rs.result = no_user;
		m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
	}
}

//11.处理添加好友回复
void CKernel::dealAddFriendRS(char* buf, int len, long Ip)
{
	cout << "CKernel::dealAddFriendRS" << endl;
	//1.拆包
	STRU_ADD_RS* rs = (STRU_ADD_RS*)buf;
	//2.判断添加好友结果
	if (rs->result == add_friend_success)
	{
		//3.写入好友关系到数据库中
		char sqlBuf[TCP_SQL_SIZE];
		memset(sqlBuf, 0, TCP_SQL_SIZE);
		sprintf_s(sqlBuf, "insert into t_friend values(%d,%d);", rs->UserId, rs->frinedId);
		if (!sql.UpdateMySql(sqlBuf))
		{
			cout << "update mysql error" << sqlBuf << endl;
			return;
		}
		sprintf_s(sqlBuf, "insert into t_friend values(%d,%d);", rs->frinedId, rs->UserId);
		if (!sql.UpdateMySql(sqlBuf))
		{
			cout << "update mysql error" << sqlBuf << endl;
			return;
		}
	}
	//4.将结果转发给客户端
	m_pMediator->SendData( buf, len, m_mapIdToSocket[rs->frinedId]);
	//更新好友列表
	getUserList(rs->UserId);
	getUserList(rs->frinedId);
}

//12.处理下线请求
void CKernel::dealOfflineRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealOfflineRQ" << endl;
	//1.拆包
	STRU_OFFLINE_RQ* rq = (STRU_OFFLINE_RQ*)buf;
	//2.根据用户ID查询好友ID列表
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select idB from t_friend where idA=%d;", rq->userID);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error：" << sqlBuf << endl;
		return;
	}
	//3.遍历好友ID列表，依次发送下线
	int friendId = 0;
	while (res.size() > 0)
	{
		//4.取出id
		friendId = atoi(res.front().c_str());
		res.pop_front();

		//5.判断是否在线
		if (m_mapIdToSocket.count(friendId) > 0)
		{
			//6.转发下线请求
			m_pMediator->SendData(buf, len, m_mapIdToSocket[friendId]);
		}
	}
	//7.移除下线用户的socket
	if (m_mapIdToSocket.count(rq->userID) > 0)
	{
		m_mapIdToSocket.erase(rq->userID);
	}
}

string CKernel::getMD5(const char* val)
{
	string buf;
	buf += val;
	buf += "_";
	buf += TCP_MD5;
	MD5 md(buf);
	cout<< buf<<" md5: " <<md.toString()<<endl;
	return md.toString();
}

// 处理群聊创建请求
void CKernel::dealOurChatRQ(char* buf, int nLen, long ISendIP)
{
	cout << "CKernel::dealOurChatRQ" << endl;
	STRU_OURCHAT_RQ* rq = (STRU_OURCHAT_RQ*)buf;
	//1.先查找群聊号的最大值
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select ifnull(max(id_link),0) from t_ourchat;");
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	int maxid;
	maxid = atoi(res.front().c_str())+1;
	res.pop_front();
	//2.创建群聊
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "insert into t_ourchat values(%d,%d);", maxid, rq->userID);
	if (!sql.UpdateMySql(sqlBuf))
	{
		cout << "update mysql error" << sqlBuf << endl;
		return;
	}
	for (int i = 0; i < TCP_SELECT_NUMBER; i++)
	{
		if (rq->FriendID[i]!= 0)
		{
			sprintf_s(sqlBuf, "insert into t_ourchat values(%d,%d);", maxid, rq->FriendID[i]);
			if (!sql.UpdateMySql(sqlBuf))
			{
				cout << "update mysql error" << sqlBuf << endl;
				return;
			}
		}
		else
		{
			break;
		}
	}
	//3.返回群id
	STRU_OURCHAT_RS rs;
	rs.ourChatID = maxid;
	rs.result = create_success;
	m_pMediator->SendData((char*)&rs, sizeof(rs), m_mapIdToSocket[rq->userID]);
	
	//返回群列表
	getOurChatList(maxid, rq->userID);
	
	for (int i = 0; i < TCP_SELECT_NUMBER; i++)
	{
		if (rq->FriendID[i] != 0)
		{
			getOurChatList(maxid, rq->FriendID[i]);
		}
		else
		{
			break;
		}
	}
}
// 得到群聊联系人列表
void CKernel::getOurChatList(int ourChatID,int UserID)
{
	cout << "CKernel::getUserList" << endl;

	//3.根据群聊的ID查询好友列表
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id_user from t_ourchat where id_link=%d;", ourChatID);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	//4.将多个列表的信息发送给自己
	int userID;
	STRU_TCP_OUR_CHAT_INFO UserInfo;

	while (res.size() > 0)
	{
		//5.拿到用户列表的ID
		userID = atoi(res.front().c_str());
		res.pop_front();

		//6.得到好友的信息
		getUserInfoByID(userID, &UserInfo);
		UserInfo.OurChatId = ourChatID;
		//7.发送给客户端
		m_pMediator->SendData((char*)&UserInfo, sizeof(UserInfo), m_mapIdToSocket[UserID]);
		
		
	}
}

//处理群聊消息的请求
void CKernel::dealOurChatTalkRQ(char* buf, int nLen, long ISendIP)
{
	cout<< "CKernel::dealOurChatTalkRQ" << endl;
	STRU_OURCHAT_TALK_RQ* rq = (STRU_OURCHAT_TALK_RQ*)buf;

	//2.根据群聊查找好友id ,name
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id_user,name from t_ourchat o inner join t_user u on o.id_user = u.id where id_link = %d;", rq->OurChatId);
	if (!sql.SelectMySql(sqlBuf, 2, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}

	int friendid;

	while (res.size() > 0)
	{
		friendid = atoi(res.front().c_str());
		res.pop_front();
		strcpy(rq->name, res.front().c_str());
		res.pop_front();
		//3.如果在线就正常转发，不在线就不发
		if (m_mapIdToSocket.count(friendid) > 0)
		{
			//4.如果存在，就直接转发
			m_pMediator->SendData(buf, nLen, m_mapIdToSocket[friendid]);
		}
	}
}

// 处理发送文件信息请求
void CKernel::dealFileInfoRQ(char* buf, int nLen, long ISendIP)
{
	//解包
	STRU_SEND_FILE_RQ* rq = (STRU_SEND_FILE_RQ*)buf;
	//根据姓名 查找好友id
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id from t_user where name = '%s';", rq->friend_name);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	int friendid;
	if (res.size() == 0)
	{
		cout << sqlBuf << endl;
		return;
	}
	friendid = atoi(res.front().c_str());
	res.pop_front();
	STRU_SEND_FILE_RS rs;
	int userid = rq->userid;
	rs.userid = friendid;
	//查看是否在线，不在线就回复
	if (m_mapIdToSocket.count(friendid) == 0)
	{
		rs.result = friend_offline;
		m_pMediator->SendData((char*)&rs, sizeof(rs), m_mapIdToSocket[userid]);
		return;
	}
	//查看文件大小是否合理
	if (rq->size == TCP_FILE_SIZE)
	{
		//不合理就回复
		rs.result = out_range;
		m_pMediator->SendData((char*)&rs, sizeof(rs), m_mapIdToSocket[userid]);
		return;
	}

	//合理就转发
	m_pMediator->SendData(buf, nLen, m_mapIdToSocket[friendid]);
}
// 处理发送文件信息响应
void CKernel::dealFileInfoRS(char* buf, int nLen, long ISendIP)
{
	STRU_SEND_FILE_RS* rs = (STRU_SEND_FILE_RS*)buf;
	//根据姓名 查找好友id
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id from t_user where name = '%s';", rs->friend_name);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	if (res.size() == 0)
	{
		return;
	}
	int friendid;
	friendid = atoi(res.front().c_str());
	res.pop_front();
	if (rs->result == accept_file)
	{
		//查看是否在线，不在线就回复
		if (m_mapIdToSocket.count(friendid) == 0)
		{
			STRU_SEND_FILE_RS rs2;
			rs2.result = friend_offline;
			m_pMediator->SendData((char*)&rs2, sizeof(rs2), m_mapIdToSocket[rs->userid]);
			return;
		}
	}
	//直接转发
	m_pMediator->SendData(buf,nLen,m_mapIdToSocket[friendid]);
}
// 处理发送文件块请求
void CKernel::dealFileBlockRQ(char* buf, int nLen, long ISendIP)
{
	STRU_FILE_RQ* rq = (STRU_FILE_RQ*)buf;
	//根据姓名 查找好友id
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id from t_user where name = '%s';", rq->friend_name);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	if (res.size() == 0)
	{
		return;
	}
	int friendid;
	friendid = atoi(res.front().c_str());
	res.pop_front();
	//查看是否在线，不在线就回复
	if (m_mapIdToSocket.count(friendid) == 0)
	{
		STRU_SEND_FILE_RS rs2;
		rs2.result = friend_offline;
		m_pMediator->SendData((char*)&rs2, sizeof(rs2), m_mapIdToSocket[rq->userid]);
		return;
	}
	m_pMediator->SendData(buf, nLen
		, m_mapIdToSocket[friendid]);
}
// 处理发送文件块响应
void CKernel::dealFileBlockRS(char* buf, int nLen, long ISendIP)
{
	STRU_FILE_RS* rs = (STRU_FILE_RS*)buf;
	//根据姓名 查找好友id
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id from t_user where name ='%s';", rs->friend_name);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	if (res.size() == 0)
	{
		cout << sqlBuf <<" "<< rs->friend_name << endl;
		return;
	}
	int friendid;
	friendid = atoi(res.front().c_str());
	res.pop_front();
	//查看是否在线，不在线就回复
	if (m_mapIdToSocket.count(friendid) == 0)
	{
		STRU_SEND_FILE_RS rs2;
		rs2.result = friend_offline;
		m_pMediator->SendData((char*)&rs2, sizeof(rs2), m_mapIdToSocket[rs->userid]);
		return;
	}
	m_pMediator->SendData(buf, nLen, m_mapIdToSocket[friendid]);
}