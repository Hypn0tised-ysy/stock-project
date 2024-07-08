#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include "My_stock.h"
#include "order.h"
#include <Qstring>
// ע�ʹ��벿��Ϊ��һ�������ù���ʵ�ַ�ʽ������������Account_group���洢�˻���Ϣ�����������ÿ���,ע�Ͳ��ַŵ���Account_group

class Account
{
private:
	std::string id;					 // �˻���id
	std::string password;			 // �˻�������
	double money;					 // �˻������
	std::vector<My_stock *> mystock; // �洢��Ʊ��Ϣ�����Դ洢�����ͬ���͵Ĺ�Ʊ
	// std::vector<Account*>acc;//�洢�˻����壬�������õ������Ϊ���ݴ洢���÷������ⲿ����һ��Account��Ķ���ͨ�����øö����acc���洢�˻���Ϣ
	friend class Account_group;

public:
	// int enroll(std::string _id,std::string _password);//ע��
	// void setid(Account *user,bool &reg,std::string s);//�����˺�
	// void setpassword(Account *user,std::string s);//��������
	Account() {}
	// bool check(std::string id, std::string pass);//����˺��Ƿ���ȷ
	bool is_oktobuy(double price, Account *user); // �Ƿ����㹻�Ľ�Ǯ�ܹ�ȥ������Ʒ
	// Account*Getaccount(bool is_ok);//������ж��Ƿ�ע��ɹ����ɹ��ͷ���ע��ɹ����˻�ָ��
	std::string get_id(Account *user);									  // �鿴�ҵ��˻�id
	std::vector<My_stock *> show_my_stock();							  // �鿴�ҵĹ�Ʊ�����Ϣ
	void upgrade(std::string _sym, int _sum, double price, Order &order); // ���¿����Ϣ
	// Account* find_user(std::string _id);//�ҵ�ָ����id���û�
	void setmoney(double mm);
	Account(std::string _id, std::string _password, double _money); // ���캯��
};

// ���ڹ���ͳ��۶����������Ӷ���������
// ���Ӷ����ĺ�������һ�������Ƕ���id���ڶ����������û���Ϣ������������������۸񣬵��ĸ����������������������������������ķ���
Order add_my_order(int order_id, Account *user, double price, int sum, std::string sym, bool side);
int enroll(std::string _id, std::string _password); // ע��
int login(std::string _id, std::string _password);	// ��¼