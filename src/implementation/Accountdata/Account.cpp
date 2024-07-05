#include "Account.h"
bool Account::enroll(std::string _id,std::string _password)
{
	Account *user = new Account();//创建一个新的用户
	bool reg = true;//检测id是否有效
		std::cout << "Please create your id" << std::endl;
		setid(user,reg,_id);//设置id
		if (!reg)//如果输入的账户id有效，开始设置密码
		{
			std::cout << "Please set your password" << std::endl;
			setpassword(user,_password);//设置密码
			user->money = 50000;//启动资金
		}
		else
		{
			return false;//输入的账户id无效重新输入
		}
	acc.push_back(user);//将新创建的账户添加进入账户列表中，暂时没有数据库，先用一个数组
	std::cout << "Congratulations,you can enter our sysytem" << std::endl;
	system("cls");//清屏幕
	return true;//输入的id有效
}
void Account::setid(Account *user,bool &reg,std::string s)
{
	if (acc.empty())
	{
		user->id = s;
		reg = false;
	}
		
	else
	{
		for (auto t : acc)
		{
			if (s == t->id)
			{
				std::cout << "somebody use this id,Please try another one" << std::endl;
				reg = true;//重新输一遍
				return;
			}
		}user->id = s;

		reg = false;
	}
}
void Account::setpassword(Account *user,std::string s)
{
	user->password= s;
}
bool Account::login(std::string _id, std::string _password)
{
	
	

		std::cout << "enter your account" << std::endl;
		if (check(_id, _password))
		{
			std::cout << "Welcome back " << std::endl;
		}
		else
		{
			std::cout << "Sorry,you put the wrong data,Plsase try again" << std::endl;
			return false;
		}
		Sleep(1000);
		system("cls");
		return true;
}
bool Account::check(std::string id, std::string pass)
{
	for (auto tem : acc)
	{
		if (tem->id != id)
		{
			continue;
		}
		else if (tem->id == id && tem->password == pass)
		{
			return true;
		}
		else
		{
			std::cout << "You may put the wrong id or wrong password" << std::endl;
		}
		
	}
	std::cout << "You may put the wrong id or wrong password" << std::endl;
	return false;
}
bool Account::is_oktobuy(double price,Account *user)
{
	if (user->money < price)
	{
		return false;
	}
	else
	{
		return true;
	}
}
Account* Account::Getaccount(bool is_ok)//可以把那个enroll的函数放在这里进行判定
{
	if (is_ok)
	{
		return acc.back();//获取当前列表的最新账户
	}
	else
	{
		return nullptr;
	}
}