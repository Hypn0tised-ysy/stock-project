#pragma once
#include "Account.h"
class Account_group
{
private:
	std::vector<Account *> acc; // 存储账户个体，真正调用的这个作为数据存储，用法：在外部定义一个Account类的对象，通过调用该对象的acc来存储账户信息

public:
	// bool enroll(std::string _id, std::string _password);//注册
	Account *find_user(std::string _id);				 // 找到指定的id的用户
	Account *Getaccount(bool is_ok);					 // 这个是判断是否注册成功，成功就返回注册成功的账户指针
	bool check(std::string id, std::string pass);		 // 检查账号是否正确
	bool login(std::string _id, std::string _password);	 // 登录
	void setid(Account *user, bool &reg, std::string s); // 设置账号
};
