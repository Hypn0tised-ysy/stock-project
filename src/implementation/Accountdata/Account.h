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
	string id;//账户名id
	string password;//账户的密码
	double money;//账户的余额
	vector<Account*>acc;//存储账户个体
	//持有的股票信息

public:
	void enroll();//注册
	void setid(Account *user,bool &reg);//设置账号
	void setpassword(Account *user);//设置密码
	void login();//登录
	bool check(string id, string pass);//检查账号是否正确
	void purchase();//购入股票
	void sell();//出售股票
	bool is_oktobuy(double price,Account *user);//是否有足够的金钱能够去购买商品
	


};

