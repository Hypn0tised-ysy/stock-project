#include "Account_group.h"
bool Account_group::enroll(std::string _id, std::string _password)
{
	Account *user = new Account();//����һ���µ��û�
	bool reg = true;//���id�Ƿ���Ч
	std::cout << "Please create your id" << std::endl;
	setid(user, reg, _id);//����id
	if (!reg)//���������˻�id��Ч����ʼ��������
	{
		std::cout << "Please set your password" << std::endl;
		user->setpassword(user, _password);//��������
		user->setmoney(50000.0);//�����ʽ�
	}
	else
	{
		return false;//������˻�id��Ч��������s
	}
	acc.push_back(user);//���´������˻���ӽ����˻��б��У���ʱû�����ݿ⣬����һ������
	My_stock*mynew = new My_stock("A", 100);
	user->mystock.push_back(mynew);
	std::cout << "Congratulations,you can enter our sysytem" << std::endl;
	return true;//�����id��Ч
}
Account* Account_group::find_user(std::string _id)//�ҵ���Ӧid���û�
{
	for (auto tem : this->acc)
	{
		if (tem->get_id(tem) == _id)
		{
			return tem;//�ҵ���ָ��id���û�
		}
	}
	return nullptr;//û�ҵ�������һ����ָ��
}

Account* Account_group::Getaccount(bool is_ok)//���԰��Ǹ�enroll�ĺ���������������ж�
{
	if (is_ok)//���ɹ�ע���˺�
	{
		return acc.back();//��ȡ��ǰ�б�������˻�
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
		if (tem->id != id)//û���ҵ���Ӧ��idʱ�򣬼�����
		{
			continue;
		}
		else if (tem->id == id && tem->password == pass)//�˺���Ϣ��ȫƥ��
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
	if (acc.empty())//����˺����ݴ洢��û���˺���Ϣ����
	{
		user->id = s;
		reg = false;
	}

	else
	{
		for (auto t : acc)//�����˻������ݴ洢��
		{
			if (s == t->id)//����������˺���Ϣ�����ݿ��д��ڵ���Ϣ���ظ���ʱ��
			{
				std::cout << "somebody use this id,Please try another one" << std::endl;
				reg = true;//������һ��
				return;
			}
		}
		user->id = s;//ע����Ϣͨ��Ҫ�󣬿���ע��

		reg = false;//�����ж�����
	}
}