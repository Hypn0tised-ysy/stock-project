#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
using namespace std;
class Account
{
private:
	string id;//�˻���id
	string password;//�˻�������
	double money;//�˻������
	vector<Account*>acc;//�洢�˻�����
	//���еĹ�Ʊ��Ϣ

public:
	void enroll();//ע��
	void setid(Account *user,bool &reg);//�����˺�
	void setpassword(Account *user);//��������
	void login();//��¼
	bool check(string id, string pass);//����˺��Ƿ���ȷ
	void purchase();//�����Ʊ
	void sell();//���۹�Ʊ
	bool is_oktobuy(double price,Account *user);//�Ƿ����㹻�Ľ�Ǯ�ܹ�ȥ������Ʒ
	


};

