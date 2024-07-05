#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>

class Account
{
private:
	std::string id;//�˻���id
	std::string password;//�˻�������
	double money;//�˻������	
	std::vector<Account*>acc;//�洢�˻�����
	//���еĹ�Ʊ��Ϣ
public:
	bool enroll(std::string _id,std::string _password);//ע��
	void setid(Account *user,bool &reg,std::string s);//�����˺�
	void setpassword(Account *user,std::string s);//��������
	bool login(std::string _id, std::string _password);//��¼
	bool check(std::string id, std::string pass);//����˺��Ƿ���ȷ
	void purchase();//�����Ʊ
	void sell();//���۹�Ʊ
	bool is_oktobuy(double price,Account *user);//�Ƿ����㹻�Ľ�Ǯ�ܹ�ȥ������Ʒ
	Account*Getaccount(bool is_ok);
};

