#include "Account.h"
bool Account::enroll(std::string _id,std::string _password)
{
	Account *user = new Account();//����һ���µ��û�
	bool reg = true;//���id�Ƿ���Ч
		std::cout << "Please create your id" << std::endl;
		setid(user,reg,_id);//����id
		if (!reg)//���������˻�id��Ч����ʼ��������
		{
			std::cout << "Please set your password" << std::endl;
			setpassword(user,_password);//��������
			user->money = 50000;//�����ʽ�
		}
		else
		{
			return false;//������˻�id��Ч��������
		}
	acc.push_back(user);//���´������˻���ӽ����˻��б��У���ʱû�����ݿ⣬����һ������
	std::cout << "Congratulations,you can enter our sysytem" << std::endl;
	system("cls");//����Ļ
	return true;//�����id��Ч
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
				reg = true;//������һ��
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
Account* Account::Getaccount(bool is_ok)//���԰��Ǹ�enroll�ĺ���������������ж�
{
	if (is_ok)
	{
		return acc.back();//��ȡ��ǰ�б�������˻�
	}
	else
	{
		return nullptr;
	}
}