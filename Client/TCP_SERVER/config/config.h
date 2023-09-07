#pragma once
#define TCP_TYPE_HEAD 1000
#define TCP_SERVER_IP "127.0.0.1"
#define TCP_PORT 3300
#define TCP_RECVBUF (4096)
#define BACK_LOG 128
#define TCP_NAME_SIZE 100
#define TCP_PROTOCAL_COUNT 20
#define TCP_CONTENT_SIZE 2048
#define TCP_INFO_SIZE 50
#define TCP_SQL_SIZE 1024
#define TCP_MD5 "9090"
#define TCP_SELECT_NUMBER 20
#define TCP_FILE_SIZE 1024*1024*1024

//ע������ͻظ�
#define TCP_REGISTER_RQ (TCP_TYPE_HEAD+10)
#define TCP_REGISTER_RS (TCP_TYPE_HEAD+11)
//��¼����ͻظ�
#define TCP_LOGIN_RQ (TCP_TYPE_HEAD+12)
#define TCP_LOGIN_RS (TCP_TYPE_HEAD+13)
//��Ӻ�������ͻظ�
#define TCP_ADD_RQ (TCP_TYPE_HEAD+14)
#define TCP_ADD_RS (TCP_TYPE_HEAD+15)
//���ѻ�����Ϣ
#define TCP_INFO (TCP_TYPE_HEAD+16) 
//��������ͻظ�
#define TCP_CHAT_RQ (TCP_TYPE_HEAD+17) //�����Ѿ������û�֮���������Ϣת��
#define TCP_CHAT_RS (TCP_TYPE_HEAD+18) //�����û������ߣ��������ظ�
//��������
#define TCP_OFFLINE_RQ (TCP_TYPE_HEAD+19)

//#Ⱥ������ͻظ�
#define TCP_OURCHAT_RQ (TCP_TYPE_HEAD+20)

#define TCP_OURCHAT_RS (TCP_TYPE_HEAD+21)

//Ⱥ�ĵĺ��ѻ�����Ϣ
#define TCP_OUR_INFO (TCP_TYPE_HEAD+22)

//Ⱥ����Ϣ������
#define TCP_OURCHAT_TALK_RQ (TCP_TYPE_HEAD+23)

//�����ļ���������ͻظ�
#define TCP_SEND_FILE_RQ (TCP_TYPE_HEAD+24)
#define TCP_SEND_FILE_RS (TCP_TYPE_HEAD+25)

//�ļ�����
#define TCP_FILE_RQ (TCP_TYPE_HEAD+26)
#define TCP_FILE_RS (TCP_TYPE_HEAD+27)

//����Э��ͷ����
typedef int PackType;

//ע����
#define register_success (0)
#define tel_has_existed (1)
#define user_is_existed (2)

//��¼���
#define login_success (0)
#define user_not_exist (1)
#define password_error (2)

//��Ӻ��ѽ��
#define add_friend_success (0)
#define user_refuse (1)
#define user_offline (2)
#define no_user (3)

//�û�״̬
#define status_online (0)
#define status_offline (1)

//��������
#define send_success (0)
#define send_fail (1)

//����Ⱥ�� 
#define create_failed (0)
#define create_success (1)

//�ļ�����״̬
#define refuse_file (0)
#define accept_file (1)
#define abrupt_pause (2)
#define out_range (3)
#define friend_offline (4)
#define accept_fail (5)
#define accepted_success (6)


//Э��Ľṹ��
/*---------------------------*/
//ע������ṹ��
typedef struct STRU_REGISTER_RQ
{
	PackType type;
	char tel[TCP_NAME_SIZE];
	char name[TCP_NAME_SIZE];
	char password[TCP_NAME_SIZE];
	STRU_REGISTER_RQ():type(TCP_REGISTER_RQ)
	{
		memset(tel, 0, TCP_NAME_SIZE);
		memset(password, 0, TCP_NAME_SIZE);
		memset(name, 0, TCP_NAME_SIZE);
	}
}STRU_REGISTER_RQ;

//ע��ظ��ṹ��
typedef struct STRU_REGISTER_RS
{
	PackType type;
	int result;
	STRU_REGISTER_RS() :type(TCP_REGISTER_RS),result(register_success)
	{

	}

}STRU_REGISTER_RS;
//��¼����ṹ��

typedef struct STRU_LOGIN_RQ
{
	PackType type;
	char tel[TCP_NAME_SIZE];
	char password[TCP_NAME_SIZE];

	STRU_LOGIN_RQ() :type(TCP_LOGIN_RQ)
	{
		memset(tel, 0, TCP_NAME_SIZE);
		memset(password, 0, TCP_NAME_SIZE);
	}

}STRU_LOGIN_RQ;

//��¼�ظ��ṹ��

typedef struct STRU_LOGIN_RS
{
	PackType type;
	int UserId;
	int result;
	STRU_LOGIN_RS() :type(TCP_LOGIN_RS),result(send_fail),UserId(0)
	{

	}
}STRU_LOGIN_RS;

//��Ӻ�������ṹ��
typedef struct STRU_ADD_RQ
{
	PackType type;
	int UserId;//ͨ��userid�����ݿ����ҵ���Ӧ����
	char username[TCP_NAME_SIZE];
	char friendname[TCP_NAME_SIZE];

	STRU_ADD_RQ() :type(TCP_ADD_RQ), UserId(0)
	{
		memset(username, 0, TCP_NAME_SIZE);
		memset(friendname, 0, TCP_NAME_SIZE);
	}
}STRU_ADD_RQ;

//��Ӻ��ѻظ��ṹ��
typedef struct STRU_ADD_RS
{
	PackType type;
	int result;
	int UserId;//�����ҵ�Ҫ���ص���
	int frinedId;
	char friendName[TCP_NAME_SIZE];
	STRU_ADD_RS() :type(TCP_ADD_RS), result(user_refuse), UserId(0), frinedId(0)
	{
		memset(friendName, 0, TCP_NAME_SIZE);
	}
}STRU_ADD_RS;
//��������ṹ��

typedef struct STRU_CHAT_RQ
{
	PackType type;
	int userId;
	int friendId;
	char content[TCP_CONTENT_SIZE];
	STRU_CHAT_RQ() :type(TCP_CHAT_RQ),userId(0),friendId(0)
	{
		memset(content, 0, TCP_CONTENT_SIZE);
	}
}STRU_CHAT_RQ;

//����ظ��ṹ��

typedef struct STRU_CHAT_RS
{
	PackType type;
	int frinedId;
	int result;
	STRU_CHAT_RS() :type(TCP_CHAT_RS), frinedId(0), result(user_offline)
	{

	}
}STRU_CHAT_RS;

//������Ϣ�ṹ��

typedef struct STRU_TCP_INFO
{
	PackType type;
	int UserId;
	int IconId;
	int status;
	char name[TCP_INFO_SIZE];
	char lable[TCP_INFO_SIZE];

	STRU_TCP_INFO() :type(TCP_INFO), UserId(0), IconId(0), status(status_online)
	{
		memset(name, 0, TCP_INFO_SIZE);
		memset(lable, 0, TCP_INFO_SIZE);
	}

}STRU_TCP_INFO;

//��������ṹ��

typedef struct STRU_OFFLINE_RQ
{
	PackType type;
	int userID;

	STRU_OFFLINE_RQ() :
		type(TCP_OFFLINE_RQ), userID(0)
	{}
}STRU_OFFLINE_RQ;

//���Ⱥ������ṹ��
typedef struct STRU_OURCHAT_RQ
{
	PackType type;
	int userID;
	int FriendID[TCP_SELECT_NUMBER];

	STRU_OURCHAT_RQ():type(TCP_OURCHAT_RQ),userID(0)
	{
		memset(FriendID, 0, sizeof(int)*(TCP_SELECT_NUMBER));
	}

}STRU_OURCHAR_RQ;

typedef struct STRU_OURCHAT_RS
{
	PackType type;
	int result;
	int ourChatID;
	STRU_OURCHAT_RS() :type(TCP_OURCHAT_RS), result(create_success), ourChatID(0)
	{

	}
}STRU_OURCHAT_RS;


typedef struct STRU_TCP_OUR_CHAT_INFO
{
	PackType type;
	int UserId;
	int IconId;
	int status;
	int OurChatId;
	char name[TCP_INFO_SIZE];
	char lable[TCP_INFO_SIZE];

	STRU_TCP_OUR_CHAT_INFO() :type(TCP_OUR_INFO), UserId(0), IconId(0), status(status_online), OurChatId(0)
	{
		memset(name, 0, TCP_INFO_SIZE);
		memset(lable, 0, TCP_INFO_SIZE);
	}

}STRU_TCP_OUR_CHAT_INFO;

typedef struct STRU_OURCHAT_TALK_RQ
{
	PackType type;
	int userId;
	int OurChatId;
	char name[TCP_NAME_SIZE];
	char content[TCP_CONTENT_SIZE];
	STRU_OURCHAT_TALK_RQ() :type(TCP_OURCHAT_TALK_RQ),userId(0),OurChatId(0)
	{
		memset(content, 0, TCP_CONTENT_SIZE);
		memset(name, 0, TCP_NAME_SIZE);
	}
}STRU_OURCHAT_TALK_RQ;

typedef struct STRU_SEND_FILE_RQ
{
	PackType type;
	int userid;
	int size;
	char FileID[TCP_NAME_SIZE];
	char file_name[TCP_NAME_SIZE];
	char friend_name[TCP_NAME_SIZE];
	STRU_SEND_FILE_RQ() :type(TCP_SEND_FILE_RQ), userid(0), size(0)
	{
		memset(friend_name, 0, TCP_NAME_SIZE);
		memset(file_name, 0, TCP_NAME_SIZE);
		memset(FileID, 0, TCP_NAME_SIZE);
	}
}STRU_SEND_FILE_RQ;

typedef struct STRU_SEND_FILE_RS
{
	PackType type;
	int userid;
	int friendid;
	int result;
	int offset;
	char friend_name[TCP_NAME_SIZE];
	STRU_SEND_FILE_RS() :type(TCP_SEND_FILE_RS), userid(0), result(refuse_file), offset(0), friendid(0)
	{
		memset(friend_name, 0, TCP_NAME_SIZE);
	}
}STRU_SEND_FILE_RS;

typedef struct STRU_FILE_RQ
{
	PackType type;
	int userid;
	int complete;
	int offset;//�����Ķϵ�����
	char friend_name[TCP_NAME_SIZE];
	char content[TCP_CONTENT_SIZE];
	STRU_FILE_RQ() :type(TCP_FILE_RQ), userid(0), complete(0), offset(0)
	{
		memset(content, 0, TCP_CONTENT_SIZE);
		memset(friend_name, 0, TCP_NAME_SIZE);

	}
}STRU_FILE_RQ;

typedef struct STRU_FILE_RS
{
	PackType type;
	int userid;
	int result;
	char friend_name[TCP_NAME_SIZE];
	STRU_FILE_RS() :type(TCP_FILE_RS), userid(0), result(accept_fail)
	{
		memset(friend_name, 0, TCP_NAME_SIZE);
	}
}STRU_FILE_RS;

