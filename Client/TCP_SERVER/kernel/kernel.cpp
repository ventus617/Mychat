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
//1.��ʼ������
bool CKernel::startServer()
{
	cout << "CKernel::startServer" << endl;
	//1.��ʼ��Э����
	setProtocolMap();
	//��ʼ���н���
	m_pMediator = new TcpMediator;
	if (!m_pMediator->OpenNet())
	{
		cout << "������ʧ��" << endl;
		return false;
	}
	//2.�������ݿ�
	sql.ConnectMySql("127.0.0.1", "root", "z9090900", "myqq");
	return true;
}
//2.�ر�����
void CKernel::closeServer()
{
	cout << "CKernel::closeServer" << endl;
	//������Դ
	if (m_pMediator)
	{
		m_pMediator->CloseNet();
		delete m_pMediator;
		m_pMediator = nullptr;
	}
	sql.DisConnect();
}

//3.��������
void CKernel::readyData(char* buf, int len, long Ip)
{
	cout << "CKernel::readyData" << endl;
	//1.ȡ��Э��ͷ
	PackType type = *(PackType*)buf;
	//2.����Э��ͷѡ���Ӧ�ĺ���
	cout << "type:" << type << endl;
	if (TypeBase(type) >= 0 && TypeBase(type) < TCP_PROTOCAL_COUNT)
	{
		//1.���������±�ȡ����Ӧ�ĺ�����ַ
		pFun pf = NetProtocolMap(type);
		if (pf)
		{
			//ͨ������ȥ������ͨ����ָ��
			(this->*pf)(buf, len, Ip);
		}
		else
		{
			cout << "pf error,pf:"<<pf << endl;
		}
	}

	//���ݴ�����ɺ��������
	delete[]buf;
	buf = nullptr;
}

//4.��ʼ��Э����
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

//5.ע�������ǳƺ͵绰���붼��unique
void CKernel::dealRegisterRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealRegisterRQ" << endl;
	//1.���
	STRU_REGISTER_RQ* rq = (STRU_REGISTER_RQ*)buf;
	//2.У���û�����������Ƿ�Ϸ�(�����ͻ���ȥ��)
	//3.���绰�����Ƿ�ע�������ѯ���ݿ�
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
	//4.У���ѯ�Ľ��
	if (res.size() > 0)
	{
		//5.�绰���뱻ע����ˣ�����ʧ��
		rs.result = tel_has_existed;
	}
	else
	{
		//6.�绰����û��ע�������ѯ�ǳ�
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
			//8.û��ע����ǳƣ��û����ݲ��뵽���ݿ���
			sprintf_s(sqlBuf, "insert into t_user (name,tel,password) values ('%s','%s','%s')", rq->name, rq->tel, rq->password);
			if (!sql.UpdateMySql(sqlBuf))
			{
				cout << "updata mysql error:" << sqlBuf << endl;
				return;
			}
			//9.����ע��ɹ�
			rs.result = register_success;
		}
	}
	//���ͻظ���
	m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
}

//6.��¼����
void CKernel::dealLogInRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealLogInRQ" << endl;
	//1.���
	STRU_LOGIN_RQ* rq = (STRU_LOGIN_RQ*)buf;
	//2.�ͻ��˼������Ϸ�
	//3.����tel��password
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
		//4.�û�������
		rs.result = user_not_exist;
	}
	else
	{
		//5.ȡ��id������
		int userid = atoi(res.front().c_str());
		res.pop_front();
		
		string password = res.front();
		res.pop_front();

		string pwd_md5;
		pwd_md5 = getMD5(rq->password);
		//6.�ж��û����������ʹ洢�����Ƿ�һ��
		if (pwd_md5!=password)
		{
			rs.result = password_error;
		}
		else
		{
			rs.result = login_success;
			rs.UserId = userid;//��֪��¼�����Լ���id
			
			m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
			
			m_mapIdToSocket[userid] = Ip;

			getUserList(userid);
			//�����Լ����ڵ�Ⱥ
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

//7.��ѯ������Ϣ
void CKernel::getUserList(int UserId)
{
	cout << "CKernel::getUserList" << endl;
	//1.�����Լ���ID��ѯ�Լ�����Ϣ
	STRU_TCP_INFO userInfo;
	getUserInfoByID(UserId,&userInfo);

	//2.���Լ�����Ϣ���ؿͻ��ˣ��ͻ��˽���
	m_pMediator->SendData((char*)&userInfo, sizeof(userInfo), m_mapIdToSocket[UserId]);

	//3.�����Լ���ID��ѯ�����б�
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select idB from t_friend where idA=%d;", UserId);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	//4.��������ѵ���Ϣ���͸��Լ�
	int friendId;
	STRU_TCP_INFO friendInfo;
	while (res.size() > 0)
	{
		//5.�õ����ѵ�ID
		friendId = atoi(res.front().c_str());
		res.pop_front();

		//6.�õ����ѵ���Ϣ
		getUserInfoByID(friendId,&friendInfo);

		//7.���͸��ͻ���
		m_pMediator->SendData((char*)&friendInfo, sizeof(friendInfo), m_mapIdToSocket[UserId]);

		//8.�жϺ����Ƿ�����
		if (m_mapIdToSocket.count(friendId) > 0)
		{
			//9.���ߺ��ѶԷ�������,Ҳ���ǰ��Լ�����Ϣ�����Է�����
			m_pMediator->SendData((char*)&userInfo, sizeof(userInfo), m_mapIdToSocket[friendId]);
		}
	}
}

//8.����ID��ѯ��Ϣ
void CKernel::getUserInfoByID(int Id, STRU_TCP_INFO* info)
{
	cout << "CKernel::getUserInfoByID" << endl;
	//1.����ID�����ݿ��в�ѯ�û�����Ϣ
	//����һ�е�ÿһ������
	list<string> res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	//ʹ��sprintf�����ո�ʽ��ӡ
	sprintf_s(sqlBuf, "select name,lable,iconId from t_user where id= %d;", Id);
	if (!sql.SelectMySql(sqlBuf, 3, res))
	{
		cout << "select from mysql error:" << sqlBuf << endl;
		return;
	}
	//2.��ȡ��ѯ�Ľ��
	if (res.size() == 3)
	{
		strcpy(info->name, res.front().c_str());
		res.pop_front();
		
		strcpy(info->lable, res.front().c_str());
		res.pop_front();

		info->IconId=atoi(res.front().c_str());
		res.pop_front();
	}
	//3.���Ը�ֵ
	info->UserId = Id;//id���Ǵ����id
	if (m_mapIdToSocket.find(Id) != m_mapIdToSocket.end())//�����socket֤������
	{
		info->status = status_online;
	}
	else
	{
		info->status = status_offline;
	}
}

//8.����ID��ѯ��Ϣ
void CKernel::getUserInfoByID(int Id, STRU_TCP_OUR_CHAT_INFO* info)
{
	cout << "CKernel::getUserInfoByID" << endl;
	//1.����ID�����ݿ��в�ѯ�û�����Ϣ
	//����һ�е�ÿһ������
	list<string> res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	//ʹ��sprintf�����ո�ʽ��ӡ
	sprintf_s(sqlBuf, "select name,lable,iconId from t_user where id= %d;", Id);
	if (!sql.SelectMySql(sqlBuf, 3, res))
	{
		cout << "select from mysql error:" << sqlBuf << endl;
		return;
	}
	//2.��ȡ��ѯ�Ľ��
	if (res.size() == 3)
	{
		strcpy(info->name, res.front().c_str());
		res.pop_front();

		strcpy(info->lable, res.front().c_str());
		res.pop_front();

		info->IconId = atoi(res.front().c_str());
		res.pop_front();
	}
	//3.���Ը�ֵ
	info->UserId = Id;//id���Ǵ����id
	if (m_mapIdToSocket.find(Id) != m_mapIdToSocket.end())//�����socket֤������
	{
		info->status = status_online;
	}
	else
	{
		info->status = status_offline;
	}
}

//9.������������
void CKernel::dealChatRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealChatRQ" << endl;
	//1.���
	STRU_CHAT_RQ* rq = (STRU_CHAT_RQ*)buf;
	//2.���ݺ���id���Һ����Ƿ�����
	if (m_mapIdToSocket.count(rq->friendId) > 0)
	{
		//3.������ڣ���ֱ��ת��
		m_pMediator->SendData(buf, len, m_mapIdToSocket[rq->friendId]);
	}
	else
	{
		//4.������Ѳ����ߣ����ؿͻ��˺��Ѳ�����
		STRU_CHAT_RS rs;
		rs.result = send_fail;
		rs.frinedId = rq->friendId;
		m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
	}
}

//10.������Ӻ�������
void CKernel::dealAddFriendRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealAddFriendRQ" << endl;
	//1.���
	STRU_ADD_RQ* rq = (STRU_ADD_RQ*)buf;
	//2.���ݺ����ǳƲ�ѯ����id
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id from t_user where name ='%s';", rq->friendname);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	//3.�����Ƿ����
	if (res.size() > 0)
	{
		//4.������Ѵ��ڣ�ȡ������id
		int friendID = atoi(res.front().c_str());
		res.pop_front();
		//5.��ѯ�Ƿ�����
		if (m_mapIdToSocket.count(friendID) > 0)
		{
			//6.����������ߣ�ת����Ӻ���������Է�
			m_pMediator->SendData(buf, len, m_mapIdToSocket[friendID]);
		}
		else
		{
			//7.���Ѳ����ߣ��ظ����Ѳ�����
			STRU_ADD_RS rs;
			strcpy(rs.friendName, rq->friendname);
			rs.result = user_offline;
			m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
		}
	}
	else
	{
		//8.���Ѳ�����
		STRU_ADD_RS rs;
		strcpy(rs.friendName, rq->friendname);
		rs.result = no_user;
		m_pMediator->SendData((char*)&rs, sizeof(rs), Ip);
	}
}

//11.������Ӻ��ѻظ�
void CKernel::dealAddFriendRS(char* buf, int len, long Ip)
{
	cout << "CKernel::dealAddFriendRS" << endl;
	//1.���
	STRU_ADD_RS* rs = (STRU_ADD_RS*)buf;
	//2.�ж���Ӻ��ѽ��
	if (rs->result == add_friend_success)
	{
		//3.д����ѹ�ϵ�����ݿ���
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
	//4.�����ת�����ͻ���
	m_pMediator->SendData( buf, len, m_mapIdToSocket[rs->frinedId]);
	//���º����б�
	getUserList(rs->UserId);
	getUserList(rs->frinedId);
}

//12.������������
void CKernel::dealOfflineRQ(char* buf, int len, long Ip)
{
	cout << "CKernel::dealOfflineRQ" << endl;
	//1.���
	STRU_OFFLINE_RQ* rq = (STRU_OFFLINE_RQ*)buf;
	//2.�����û�ID��ѯ����ID�б�
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select idB from t_friend where idA=%d;", rq->userID);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error��" << sqlBuf << endl;
		return;
	}
	//3.��������ID�б����η�������
	int friendId = 0;
	while (res.size() > 0)
	{
		//4.ȡ��id
		friendId = atoi(res.front().c_str());
		res.pop_front();

		//5.�ж��Ƿ�����
		if (m_mapIdToSocket.count(friendId) > 0)
		{
			//6.ת����������
			m_pMediator->SendData(buf, len, m_mapIdToSocket[friendId]);
		}
	}
	//7.�Ƴ������û���socket
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

// ����Ⱥ�Ĵ�������
void CKernel::dealOurChatRQ(char* buf, int nLen, long ISendIP)
{
	cout << "CKernel::dealOurChatRQ" << endl;
	STRU_OURCHAT_RQ* rq = (STRU_OURCHAT_RQ*)buf;
	//1.�Ȳ���Ⱥ�ĺŵ����ֵ
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
	//2.����Ⱥ��
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
	//3.����Ⱥid
	STRU_OURCHAT_RS rs;
	rs.ourChatID = maxid;
	rs.result = create_success;
	m_pMediator->SendData((char*)&rs, sizeof(rs), m_mapIdToSocket[rq->userID]);
	
	//����Ⱥ�б�
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
// �õ�Ⱥ����ϵ���б�
void CKernel::getOurChatList(int ourChatID,int UserID)
{
	cout << "CKernel::getUserList" << endl;

	//3.����Ⱥ�ĵ�ID��ѯ�����б�
	list<string>res;
	char sqlBuf[TCP_SQL_SIZE];
	memset(sqlBuf, 0, TCP_SQL_SIZE);
	sprintf_s(sqlBuf, "select id_user from t_ourchat where id_link=%d;", ourChatID);
	if (!sql.SelectMySql(sqlBuf, 1, res))
	{
		cout << "select mysql error:" << sqlBuf << endl;
		return;
	}
	//4.������б����Ϣ���͸��Լ�
	int userID;
	STRU_TCP_OUR_CHAT_INFO UserInfo;

	while (res.size() > 0)
	{
		//5.�õ��û��б��ID
		userID = atoi(res.front().c_str());
		res.pop_front();

		//6.�õ����ѵ���Ϣ
		getUserInfoByID(userID, &UserInfo);
		UserInfo.OurChatId = ourChatID;
		//7.���͸��ͻ���
		m_pMediator->SendData((char*)&UserInfo, sizeof(UserInfo), m_mapIdToSocket[UserID]);
		
		
	}
}

//����Ⱥ����Ϣ������
void CKernel::dealOurChatTalkRQ(char* buf, int nLen, long ISendIP)
{
	cout<< "CKernel::dealOurChatTalkRQ" << endl;
	STRU_OURCHAT_TALK_RQ* rq = (STRU_OURCHAT_TALK_RQ*)buf;

	//2.����Ⱥ�Ĳ��Һ���id ,name
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
		//3.������߾�����ת���������߾Ͳ���
		if (m_mapIdToSocket.count(friendid) > 0)
		{
			//4.������ڣ���ֱ��ת��
			m_pMediator->SendData(buf, nLen, m_mapIdToSocket[friendid]);
		}
	}
}

// �������ļ���Ϣ����
void CKernel::dealFileInfoRQ(char* buf, int nLen, long ISendIP)
{
	//���
	STRU_SEND_FILE_RQ* rq = (STRU_SEND_FILE_RQ*)buf;
	//�������� ���Һ���id
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
	//�鿴�Ƿ����ߣ������߾ͻظ�
	if (m_mapIdToSocket.count(friendid) == 0)
	{
		rs.result = friend_offline;
		m_pMediator->SendData((char*)&rs, sizeof(rs), m_mapIdToSocket[userid]);
		return;
	}
	//�鿴�ļ���С�Ƿ����
	if (rq->size == TCP_FILE_SIZE)
	{
		//������ͻظ�
		rs.result = out_range;
		m_pMediator->SendData((char*)&rs, sizeof(rs), m_mapIdToSocket[userid]);
		return;
	}

	//�����ת��
	m_pMediator->SendData(buf, nLen, m_mapIdToSocket[friendid]);
}
// �������ļ���Ϣ��Ӧ
void CKernel::dealFileInfoRS(char* buf, int nLen, long ISendIP)
{
	STRU_SEND_FILE_RS* rs = (STRU_SEND_FILE_RS*)buf;
	//�������� ���Һ���id
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
		//�鿴�Ƿ����ߣ������߾ͻظ�
		if (m_mapIdToSocket.count(friendid) == 0)
		{
			STRU_SEND_FILE_RS rs2;
			rs2.result = friend_offline;
			m_pMediator->SendData((char*)&rs2, sizeof(rs2), m_mapIdToSocket[rs->userid]);
			return;
		}
	}
	//ֱ��ת��
	m_pMediator->SendData(buf,nLen,m_mapIdToSocket[friendid]);
}
// �������ļ�������
void CKernel::dealFileBlockRQ(char* buf, int nLen, long ISendIP)
{
	STRU_FILE_RQ* rq = (STRU_FILE_RQ*)buf;
	//�������� ���Һ���id
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
	//�鿴�Ƿ����ߣ������߾ͻظ�
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
// �������ļ�����Ӧ
void CKernel::dealFileBlockRS(char* buf, int nLen, long ISendIP)
{
	STRU_FILE_RS* rs = (STRU_FILE_RS*)buf;
	//�������� ���Һ���id
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
	//�鿴�Ƿ����ߣ������߾ͻظ�
	if (m_mapIdToSocket.count(friendid) == 0)
	{
		STRU_SEND_FILE_RS rs2;
		rs2.result = friend_offline;
		m_pMediator->SendData((char*)&rs2, sizeof(rs2), m_mapIdToSocket[rs->userid]);
		return;
	}
	m_pMediator->SendData(buf, nLen, m_mapIdToSocket[friendid]);
}