#pragma once

#include"../Mediator/TcpMediator.h"
#include"../MySQL/CMySql.h"
#include"../config/config.h"
#include<iostream>
#include<map>

using namespace std;

//������ĺ���ָ��
class CKernel;
typedef void (CKernel::* pFun)(char*, int, long);

class CKernel
{
private:
	//�н�����
	INetMediator* m_pMediator;
	//���ݿ����
	CMySql sql;
public:
	static CKernel* pKernel;
	//��������
	pFun m_netProtocolMap[TCP_PROTOCAL_COUNT];
	//�������ݿ����û�ID��socket�Ķ�Ӧ��ϵ
	map<int, SOCKET>m_mapIdToSocket;

public:
	CKernel();
	~CKernel();
public:
	// ����������
	bool startServer();
	// �رշ�����
	void closeServer();
	// �����������ݣ��������ݷ��ɸ�����������
	void readyData(char* buf, int nLen,long ISendIP );
	// ��ʼ��Э������
	void setProtocolMap();
	// ��ѯ���ѵ���Ϣ�������Լ���
	void getUserList(int userID);
	// ����ID��ѯ��Ϣ
	void getUserInfoByID(int ID, STRU_TCP_INFO* info);
	void getUserInfoByID(int ID, STRU_TCP_OUR_CHAT_INFO* info);
	// ����ע������
	void dealRegisterRQ(char* buf, int nLen, long ISendIP);
	// �����¼����
	void dealLogInRQ(char* buf, int nLen, long ISendIP);
	// ������������
	void dealChatRQ(char* buf, int nLen, long ISendIP);
	// ������Ӻ�������
	void dealAddFriendRQ(char* buf, int nLen, long ISendIP);
	// ������Ӻ��ѻظ�
	void dealAddFriendRS(char* buf, int nLen, long ISendIP);
	// ������������
	void dealOfflineRQ(char* buf, int nLen, long ISendIP);
	// �������ļ���Ϣ����
	void dealFileInfoRQ(char* buf, int nLen, long ISendIP);
	// �������ļ���Ϣ��Ӧ
	void dealFileInfoRS(char* buf, int nLen, long ISendIP);
	// �������ļ�������
	void dealFileBlockRQ(char* buf, int nLen, long ISendIP);
	// �������ļ�����Ӧ
	void dealFileBlockRS(char* buf, int nLen, long ISendIP);
	// ����Ⱥ�Ĵ�������
	void dealOurChatRQ(char* buf, int nLen, long ISendIP);
	// �õ�Ⱥ����ϵ���б�
	void getOurChatList(int ourChatID,int UserID);

	//����Ⱥ����Ϣ������
	void dealOurChatTalkRQ(char* buf, int nLen, long ISendIP);

	//md5����
	static string getMD5(const char* val);
};
