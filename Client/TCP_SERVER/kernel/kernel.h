#pragma once

#include"../Mediator/TcpMediator.h"
#include"../MySQL/CMySql.h"
#include"../config/config.h"
#include<iostream>
#include<map>

using namespace std;

//定义类的函数指针
class CKernel;
typedef void (CKernel::* pFun)(char*, int, long);

class CKernel
{
private:
	//中介者类
	INetMediator* m_pMediator;
	//数据库对象
	CMySql sql;
public:
	static CKernel* pKernel;
	//函数数组
	pFun m_netProtocolMap[TCP_PROTOCAL_COUNT];
	//保存数据库中用户ID和socket的对应关系
	map<int, SOCKET>m_mapIdToSocket;

public:
	CKernel();
	~CKernel();
public:
	// 开启服务器
	bool startServer();
	// 关闭服务器
	void closeServer();
	// 处理所有数据，并把数据分派给各个处理函数
	void readyData(char* buf, int nLen,long ISendIP );
	// 初始化协议数组
	void setProtocolMap();
	// 查询好友的信息（包括自己）
	void getUserList(int userID);
	// 根据ID查询信息
	void getUserInfoByID(int ID, STRU_TCP_INFO* info);
	void getUserInfoByID(int ID, STRU_TCP_OUR_CHAT_INFO* info);
	// 处理注册请求
	void dealRegisterRQ(char* buf, int nLen, long ISendIP);
	// 处理登录请求
	void dealLogInRQ(char* buf, int nLen, long ISendIP);
	// 处理聊天请求
	void dealChatRQ(char* buf, int nLen, long ISendIP);
	// 处理添加好友请求
	void dealAddFriendRQ(char* buf, int nLen, long ISendIP);
	// 处理添加好友回复
	void dealAddFriendRS(char* buf, int nLen, long ISendIP);
	// 处理下线请求
	void dealOfflineRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件信息请求
	void dealFileInfoRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件信息响应
	void dealFileInfoRS(char* buf, int nLen, long ISendIP);
	// 处理发送文件块请求
	void dealFileBlockRQ(char* buf, int nLen, long ISendIP);
	// 处理发送文件块响应
	void dealFileBlockRS(char* buf, int nLen, long ISendIP);
	// 处理群聊创建请求
	void dealOurChatRQ(char* buf, int nLen, long ISendIP);
	// 得到群聊联系人列表
	void getOurChatList(int ourChatID,int UserID);

	//处理群聊消息的请求
	void dealOurChatTalkRQ(char* buf, int nLen, long ISendIP);

	//md5加密
	static string getMD5(const char* val);
};
