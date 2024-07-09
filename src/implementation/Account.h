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
	int id;							 // �˻����������?
	std::string Username;			 // �˻���id
	std::string password;			 // �˻�������
	double money;					 // �˻������?
	std::vector<My_stock > mystock; // �洢��Ʊ��Ϣ�����Դ洢������?����͵Ĺ��?
	// std::vector<Account*>acc;//�洢�˻����壬�������õ�������?����ݴ�?����÷������ⲿ����һ��Account��Ķ����?������øö����acc���洢�˻���Ϣ
	friend class Account_group;

public:
	// int enroll(std::string _id,std::string _password);//ע��
	// void setid(Account *user,bool &reg,std::string s);//�����˺�
	// void setpassword(Account *user,std::string s);//��������
	Account() {}
	// bool check(std::string id, std::string pass);//����˺��Ƿ����?
	bool is_oktobuy(double price); // �Ƿ����㹻�Ľ�Ǯ�ܹ�ȥ������Ʒ
	// Account*Getaccount(bool is_ok);//������ж��Ƿ��?���ɹ����ɹ��ͷ���ע��ɹ����˻�ָ��?
	std::string get_id(Account *user);									  // �鿴�ҵ��˻�id
	std::vector<My_stock *> show_my_stock();							  // �鿴�ҵĹ�Ʊ������?
	void upgrade(std::string _sym, int _sum, double price, Order &order); // ���¿�����?//
	// Account* find_user(std::string _id);//�ҵ�ָ����id���û�
	void setmoney(double mm);
	Account(int _id); // ���캯��
    std::string return_username();
    int return_id();
	int add_my_order(int &operatorId, double price, int quantity, const QString &symbol, bool side);//base the order Return orderId

};

// ���ڹ���ͳ��۶����������Ӷ���������?
// ���Ӷ����ĺ�������һ�������Ƕ���id���ڶ����������û���Ϣ������������������۸�?��ĸ����������������������������������ķ���?

int enroll(std::string _id, std::string _password); // ע��
int login(std::string _id, std::string _password);	// ��¼
