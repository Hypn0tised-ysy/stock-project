#include "Account.h"
void Account::enroll()
{
	Account *user = new Account();//创建一个新的用户
	bool reg = true;
	while (reg)
	{
		cout << "Please create your id" << endl;
		setid(user,reg);//设置id
		if (!reg)
		{
			cout << "Please set your password" << endl;
			setpassword(user);//设置密码
			user->money = 50000;//启动资金
		}
		else
		{
			continue;
		}
		
	}
	
	acc.push_back(user);//将新创建的账户添加进入账户列表中
	cout << "Congratulations,you can enter our sysytem" << endl;
	system("cls");
}
void Account::setid(Account *user,bool &reg)
{
	string s;
	getline(cin, s);
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
				cout << "somebody use this id,Please try another one" << endl;
				reg = true;//重新输一遍
				return;
			}
		}user->id = s;

		reg = false;
	}
}
void Account::setpassword(Account *user)
{
	string s;
	getline(cin, s);
	user->password= s;
}
void Account::login()
{
	string s1;
	string s2;
	while (1)
	{
		cout << "enter your account" << endl;
		getline(cin, s1);
		getline(cin, s2);
		if (check(s1, s2))
		{
			cout << "Welcome back " << endl;
			break;
		}
		else
		{
			cout << "Sorry,you put the wrong data,Plsase try again" << endl;
		}
		Sleep(1000);
		system("cls");
	}
	
}
bool Account::check(string id,string pass)
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
			cout << "You may put the wrong id or wrong password" << endl;
		}
		
	}
	cout << "You may put the wrong id or wrong password" << endl;
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