#include "Account.h"
//bool Account::enroll(std::string _id,std::string _password)
//{
//	Account *user = new Account();//����һ���µ��û�
//	bool reg = true;//���id�Ƿ���Ч
//		std::cout << "Please create your id" << std::endl;
//		setid(user,reg,_id);//����id
//		if (!reg)//���������˻�id��Ч����ʼ��������
//		{
//			std::cout << "Please set your password" << std::endl;
//			setpassword(user,_password);//��������
//			user->money = 50000;//�����ʽ�
//		}
//		else
//		{
//			return false;//������˻�id��Ч��������
//		}
//	acc.push_back(user);//���´������˻���ӽ����˻��б��У���ʱû�����ݿ⣬����һ������
//	My_stock*mynew = new My_stock("A",100);
//	user->mystock.push_back(mynew);
//	std::cout << "Congratulations,you can enter our sysytem" << std::endl;
//	//system("cls");//����Ļ
//	return true;//�����id��Ч
//}





//void Account::setid(Account *user,bool &reg,std::string s)
//{
//	if (acc.empty())//����˺����ݴ洢��û���˺���Ϣ����
//	{
//		user->id = s;
//		reg = false;
//	}
//		
//	else
//	{
//		for (auto t : acc)//�����˻������ݴ洢��
//		{
//			if (s == t->id)//����������˺���Ϣ�����ݿ��д��ڵ���Ϣ���ظ���ʱ��
//			{
//				std::cout << "somebody use this id,Please try another one" << std::endl;
//				reg = true;//������һ��
//				return;
//			}
//		}
//		user->id = s;//ע����Ϣͨ��Ҫ�󣬿���ע��
//
//		reg = false;//�����ж�����
//	}
//}




void Account::setpassword(Account *user,std::string s)
{
	user->password= s;
}
void Account::setmoney(double mm)
{
	this->money = mm;
}




//bool Account::login(std::string _id, std::string _password)
//{
//	
//	
//
//		std::cout << "enter your account" << std::endl;
//		if (check(_id, _password))
//		{
//			std::cout << "Welcome back " << std::endl;
//		}
//		else
//		{
//			std::cout << "Sorry,you put the wrong data,Plsase try again" << std::endl;
//			return false;
//		}
//		//Sleep(1000);
//		//system("cls");
//		return true;
//}




//bool Account::check(std::string id, std::string pass)
//{
//	for (auto tem : acc)
//	{
//		if (tem->id != id)//û���ҵ���Ӧ��idʱ�򣬼�����
//		{
//			continue;
//		}
//		else if (tem->id == id && tem->password == pass)//�˺���Ϣ��ȫƥ��
//		{
//			return true;
//		}
//		else
//		{
//			std::cout << "You may put the wrong id or wrong password" << std::endl;
//		}
//		
//	}
//	std::cout << "You may put the wrong id or wrong password" << std::endl;
//	return false;
//}



bool Account::is_oktobuy(double price,Account *user)
{
	if (user->money < price)//������������������ʱ��
	{
		return false;
	}
	else
	{
		return true;
	}
}
//Account* Account::Getaccount(bool is_ok)//���԰��Ǹ�enroll�ĺ���������������ж�
//{
//	if (is_ok)//���ɹ�ע���˺�
//	{
//		return acc.back();//��ȡ��ǰ�б�������˻�
//	}
//	else
//	{
//		return nullptr;
//	}
//}
std::string Account::get_id(Account *user)
{
	return user->id;
}
std::vector<My_stock*> Account::show_my_stock()
{
	return mystock;
}
Order add_my_order(int order_id, Account*user, double price, int sum,std::string sym, bool side)
{
	
	std::vector<My_stock*>my = user->show_my_stock();//��������һ�����������������������Կ�����ʲôӰ��
	if (!side)//���붩��
	{
		if (user->is_oktobuy(price*sum, user))//�Ƿ����㹻�Ľ��ȥ�ύ���붩��
		{
			Order  mynew =Order(order_id, user->get_id(user), price, sum, sym, side);//�������붩��
			std::cout << "����Ϊ����������" << std::endl;
			return mynew;
		}
		else
		{
			std::cout << "����" << std::endl;
			Order  error = Order();//�ն�������ʱ����ô�жϴ���
			return error;
		}
	}
	else//��������--ƥ���Լ��Ŀ���Ƿ��ж�Ӧ���ŵĹ�Ʊ�Ͷ�Ӧ�������Ĺ�Ʊ
	{
		if (my.empty())//����ҵĲֿ�Ϊ��
		{
			std::cout << "�ֿ�Ϊ�գ��޷�����" << std::endl;
			Order  error = Order();//�������붩��
			return error;
		}
		for (auto tem : my)//�����������
		{
			if (tem->get_name() == sym)//�����Լ��Ŀ�����ҵ��˶�Ӧ�Ĺ�Ʊ����
			{
				if (sum <= tem->get_sum())//�����Լ���������㹻���ύ��������
				{
					Order mynew =  Order(order_id, user->get_id(user), price, sum, sym, side);//��������
					return mynew;
				}
				else//����й���������������ô�ඩ��
				{
					std::cout << "��������㣬�޷�����" << sum << "��������������������" << std::endl;
					Order  error = Order();//�ն�������ʱ����ô�жϴ���
					return error;
				}
			}
			
		}
		std::cout << "��Ŀ����û�������Ʊ���޷�������������" << std::endl;
		Order  error = Order();//�ն�������ʱ����ô�жϴ���
		return error;
	}
	
}
//Account*Account::find_user(std::string _id)//�ҵ���Ӧid���û�
//{
//	for (auto tem : this->acc)
//	{
//		if (tem->get_id(tem) == _id)
//		{
//			return tem;//�ҵ���ָ��id���û�
//		}
//	}
//	return nullptr;//û�ҵ�������һ����ָ��
//}



void Account::upgrade(std::string _sym, int _sum, double price, Order&order)//���¿����Ϣ,����ָ���ļ۸�
{
	if (!order.side)//�����������Ϣ
	{
		this->money -= price;//����Ҫ��Ǯ��  
		if (this -> mystock.empty())//����ֿ�Ϊ��
		{
			My_stock*my_new = new My_stock(_sym, _sum);
			this->mystock.push_back(my_new);//���µĹ�Ʊ��Ϣ�洢��������
		}
		else//����ֿⲻΪ��
		{
			bool is_find = false;//�Ƿ��ҵ��и��ֹ�Ʊ
			for (auto tem : mystock)
			{
				if (tem->get_name() == _sym)//���������������Ʊ���ͽ�������
				{
					tem->setnew_sum(tem->get_sum() + _sum);//�����µ�����
					is_find = true;
					break;
				}
			}
			//��������û�����ֹ�Ʊ���Ǿ���ӽ�ȥ
			if (!is_find)
			{
				My_stock*my_new = new My_stock(_sym, _sum);
				this->mystock.push_back(my_new);//���µĹ�Ʊ��Ϣ�洢��������
			}
			
		}
		
	}
	else//�����������Ϣ,//֮ǰ�Ѿ��ж����ֿ�Ҫ�ж�Ӧ����������������������Ӧ��Ĭ�ϲֿ����ж�Ӧ�Ķ�����
	{
		for (auto tem : mystock)
		{
			if (_sym == tem->get_name())//�ҵ��˲ֿ�Ŀ����
			{
				tem->setnew_sum(tem->get_sum() - _sum);//���¿�������
				this->money += price;//׬Ǯ��
				break;
			}
		}
	}
}

//ע�Ͳ���Ϊ��һ�������ù���ʵ�ַ�ʽ�����������Account_group���洢�˻���Ϣ�����������ÿ���