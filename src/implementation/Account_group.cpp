#include "Account_group.h"
bool Account_group::enroll(std::string _id, std::string _password)
{
	Account *user = new Account();//创建一个新的用户
	bool reg = true;//检测id是否有效
	std::cout << "Please create your id" << std::endl;
	setid(user, reg, _id);//设置id
	if (!reg)//如果输入的账户id有效，开始设置密码
	{
		std::cout << "Please set your password" << std::endl;
		user->setpassword(user, _password);//设置密码
		user->setmoney(50000.0);//启动资金
	}
	else
	{
		return false;//输入的账户id无效重新输入s
	}
	acc.push_back(user);//将新创建的账户添加进入账户列表中，暂时没有数据库，先用一个数组
	My_stock*mynew = new My_stock("A", 100);
	user->mystock.push_back(mynew);
	std::cout << "Congratulations,you can enter our sysytem" << std::endl;
	return true;//输入的id有效
}
Account* Account_group::find_user(std::string _id)//找到对应id的用户
{
	for (auto tem : this->acc)
	{
		if (tem->get_id(tem) == _id)
		{
			return tem;//找到了指定id的用户
		}
	}
	return nullptr;//没找到，返回一个空指针
}

Account* Account_group::Getaccount(bool is_ok)//可以把那个enroll的函数放在这里进行判定
{
	if (is_ok)//当成功注册账号
	{
		return acc.back();//获取当前列表的最新账户
	}
	else
	{
		return nullptr;
	}
}

bool Account_group::check(std::string id, std::string pass)
{
	for (auto tem : acc)
	{
		if (tem->id != id)//没有找到对应的id时候，继续找
		{
			continue;
		}
		else if (tem->id == id && tem->password == pass)//账号信息完全匹配
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


bool Account_group::login(std::string _id, std::string _password)
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
	return true;
}

void Account_group::setid(Account *user, bool &reg, std::string s)
{
	if (acc.empty())//如果账号数据存储中没有账号信息，则
	{
		user->id = s;
		reg = false;
	}

	else
	{
		for (auto t : acc)//遍历账户的数据存储库
		{
			if (s == t->id)//当你输入的账号信息与数据库中存在的信息有重复的时候
			{
				std::cout << "somebody use this id,Please try another one" << std::endl;
				reg = true;//重新输一遍
				return;
			}
		}
		user->id = s;//注册信息通过要求，可以注册

		reg = false;//更改判定条件
	}
}