#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include"My_stock.h"
#include"order.h"

//注释代码部分为第一版曾经用过的实现方式，现在添加了Account_group来存储账户信息，看起来更好看了,注释部分放到了Account_group



class Account
{
private:
	std::string id;//账户名id
	std::string password;//账户的密码
	double money;//账户的余额	
	std::vector<My_stock*>mystock;//存储股票信息，可以存储多个不同类型的股票
	//std::vector<Account*>acc;//存储账户个体，真正调用的这个作为数据存储，用法：在外部定义一个Account类的对象，通过调用该对象的acc来存储账户信息
	friend class Account_group;

public:
	//int enroll(std::string _id,std::string _password);//注册
	//void setid(Account *user,bool &reg,std::string s);//设置账号
	//void setpassword(Account *user,std::string s);//设置密码
	
	//bool check(std::string id, std::string pass);//检查账号是否正确
	bool is_oktobuy(double price,Account *user);//是否有足够的金钱能够去购买商品
	//Account*Getaccount(bool is_ok);//这个是判断是否注册成功，成功就返回注册成功的账户指针
	std::string get_id(Account *user);//查看我的账户id
	std::vector<My_stock*> show_my_stock();//查看我的股票库存信息
	void upgrade(std::string _sym,int _sum,double price,Order &order);//更新库存信息
	Account* find_user(std::string _id);//找到指定的id的用户
	void setmoney(double mm);
	Account(std::string _id, std::string _password,double _money);//构造函数
};





//现在购买和出售都集成再添加订单这里了
//添加订单的函数，第一个参数是订单id，第二个参数是用户信息，第三个参数是意向价格，第四个参数是数量，第五个参数是买入和卖出的方向
Order add_my_order(int order_id,Account*user,double price,int sum,std::string sym,bool side);
int enroll(std::string _id, std::string _password);//注册
int login(std::string _id, std::string _password);//登录