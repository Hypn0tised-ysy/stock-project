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
	std::string id;//账户名id
	std::string password;//账户的密码
	double money;//账户的余额	
	std::vector<Account*>acc;//存储账户个体
	//持有的股票信息
public:
	bool enroll(std::string _id,std::string _password);//注册
	void setid(Account *user,bool &reg,std::string s);//设置账号
	void setpassword(Account *user,std::string s);//设置密码
	bool login(std::string _id, std::string _password);//登录
	bool check(std::string id, std::string pass);//检查账号是否正确
	void purchase();//购入股票
	void sell();//出售股票
	bool is_oktobuy(double price,Account *user);//是否有足够的金钱能够去购买商品
	Account*Getaccount(bool is_ok);
};

