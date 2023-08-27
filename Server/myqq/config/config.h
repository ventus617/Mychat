#pragma once
#define TCP_TYPE_HEAD 1000
#define TCP_SERVER_IP "127.0.0.1"
#define TCP_PORT 3300
#define TCP_RECVBUF (4096)
#define BACK_LOG 2048
#define TCP_NAME_SIZE 100
#define TCP_PROTOCAL_COUNT 20
#define TCP_CONTENT_SIZE 2048
#define TCP_INFO_SIZE 50
#define TCP_SQL_SIZE 1024
#define TCP_MD5 "9090"
#define TCP_SELECT_NUMBER 20
#define TCP_FILE_SIZE 1024*1024*1024
#define _INCREASE_THREAD 20
#define _THREAD_REDUCE 20
#define _EPOLL_MAX 20000
#define _TMIN 200
#define _TMAX 20000
#define _CMAX 40000
#include<string.h>
#define TRUE                true
#define FALSE               false
typedef int SOCKET;


/*-------------数据库信息-----------------*/
#define _DEF_DB_NAME    "myqq"
#define _DEF_DB_IP      "localhost"
#define _DEF_DB_USER    "root"
#define _DEF_DB_PWD     "z9090900"

//注册请求和回复
#define TCP_REGISTER_RQ (TCP_TYPE_HEAD+10)
#define TCP_REGISTER_RS (TCP_TYPE_HEAD+11)
//登录请求和回复
#define TCP_LOGIN_RQ (TCP_TYPE_HEAD+12)
#define TCP_LOGIN_RS (TCP_TYPE_HEAD+13)
//添加好友请求和回复
#define TCP_ADD_RQ (TCP_TYPE_HEAD+14)
#define TCP_ADD_RS (TCP_TYPE_HEAD+15)
//好友基本信息
#define TCP_INFO (TCP_TYPE_HEAD+16) 
//聊天请求和回复
#define TCP_CHAT_RQ (TCP_TYPE_HEAD+17) //用于已经在线用户之间聊天的信息转发
#define TCP_CHAT_RS (TCP_TYPE_HEAD+18) //用于用户不在线，服务器回复
//下线请求
#define TCP_OFFLINE_RQ (TCP_TYPE_HEAD+19)

//#群聊请求和回复
#define TCP_OURCHAT_RQ (TCP_TYPE_HEAD+20)

#define TCP_OURCHAT_RS (TCP_TYPE_HEAD+21)

//群聊的好友基本信息
#define TCP_OUR_INFO (TCP_TYPE_HEAD+22)

//群聊消息的请求
#define TCP_OURCHAT_TALK_RQ (TCP_TYPE_HEAD+23)

//定义文件传输请求和回复
#define TCP_SEND_FILE_RQ (TCP_TYPE_HEAD+24)
#define TCP_SEND_FILE_RS (TCP_TYPE_HEAD+25)

//文件传输
#define TCP_FILE_RQ (TCP_TYPE_HEAD+26)
#define TCP_FILE_RS (TCP_TYPE_HEAD+27)

//定义协议头类型
typedef int PackType;

//注册结果
#define register_success (0)
#define tel_has_existed (1)
#define user_is_existed (2)

//登录结果
#define login_success (0)
#define user_not_exist (1)
#define password_error (2)

//添加好友结果
#define add_friend_success (0)
#define user_refuse (1)
#define user_offline (2)
#define no_user (3)

//用户状态
#define status_online (0)
#define status_offline (1)

//发送聊天
#define send_success (0)
#define send_fail (1)

//建立群聊 
#define create_failed (0)
#define create_success (1)

//文件传输状态
#define refuse_file (0)
#define accept_file (1)
#define abrupt_pause (2)
#define out_range (3)
#define friend_offline (4)
#define accept_fail (5)
#define accepted_success (6)


//协议的结构体
/*---------------------------*/
//注册请求结构体
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

//注册回复结构体
typedef struct STRU_REGISTER_RS
{
	PackType type;
	int result;
	STRU_REGISTER_RS() :type(TCP_REGISTER_RS),result(register_success)
	{

	}

}STRU_REGISTER_RS;
//登录请求结构体

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

//登录回复结构体

typedef struct STRU_LOGIN_RS
{
	PackType type;
	int UserId;
	int result;
	STRU_LOGIN_RS() :type(TCP_LOGIN_RS),result(send_fail),UserId(0)
	{

	}
}STRU_LOGIN_RS;

//添加好友请求结构体
typedef struct STRU_ADD_RQ
{
	PackType type;
	int UserId;//通过userid在数据库中找到对应的项
	char username[TCP_NAME_SIZE];
	char friendname[TCP_NAME_SIZE];

	STRU_ADD_RQ() :type(TCP_ADD_RQ), UserId(0)
	{
		memset(username, 0, TCP_NAME_SIZE);
		memset(friendname, 0, TCP_NAME_SIZE);
	}
}STRU_ADD_RQ;

//添加好友回复结构体
typedef struct STRU_ADD_RS
{
	PackType type;
	int result;
	int UserId;//方便找到要发回的人
	int frinedId;
	char friendName[TCP_NAME_SIZE];
	STRU_ADD_RS() :type(TCP_ADD_RS), result(user_refuse), UserId(0), frinedId(0)
	{
		memset(friendName, 0, TCP_NAME_SIZE);
	}
}STRU_ADD_RS;
//聊天请求结构体

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

//聊天回复结构体

typedef struct STRU_CHAT_RS
{
	PackType type;
	int frinedId;
	int result;
	STRU_CHAT_RS() :type(TCP_CHAT_RS), frinedId(0), result(user_offline)
	{

	}
}STRU_CHAT_RS;

//好友信息结构体

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

//下线请求结构体

typedef struct STRU_OFFLINE_RQ
{
	PackType type;
	int userID;

	STRU_OFFLINE_RQ() :
		type(TCP_OFFLINE_RQ), userID(0)
	{}
}STRU_OFFLINE_RQ;

//添加群聊请求结构体
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
	int offset;//待做的断点续传
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

