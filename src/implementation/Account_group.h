#pragma once
#include "Account.h"
class Account_group
{
private:
	std::vector<Account *> acc; // �洢�˻����壬�������õ������Ϊ���ݴ洢���÷������ⲿ����һ��Account��Ķ���ͨ�����øö����acc���洢�˻���Ϣ

public:
	// bool enroll(std::string _id, std::string _password);//ע��
	Account *find_user(std::string _id);				 // �ҵ�ָ����id���û�
	Account *Getaccount(bool is_ok);					 // ������ж��Ƿ�ע��ɹ����ɹ��ͷ���ע��ɹ����˻�ָ��
	bool check(std::string id, std::string pass);		 // ����˺��Ƿ���ȷ
	bool login(std::string _id, std::string _password);	 // ��¼
	void setid(Account *user, bool &reg, std::string s); // �����˺�
};
