#include "Account.h"
#include "../database/database.h"
#include <QVariantList>
extern Database db;
Account::Account(int _id)
{
	id = _id;
	QVariantList QVuser = db.getUser(_id);
	Username = QVuser[1].toString().toStdString();
	password = QVuser[2].toString().toStdString();
	money = QVuser[3].toDouble();
}

int enroll(std::string _id, std::string _password)
{
	QString Username = QString::fromStdString(_id);
	QString password = QString::fromStdString(_password);
	return db.addUser(Username, password, 50000);
}
std::string Account::return_username()
{
    return Username;
}
int Account::return_id()
{
    return id;
}
double Account::return_money()
{
    return money;
}
// void Account::setid(Account *user,bool &reg,std::string s)
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
// }

// void Account::setpassword(Account *user,std::string s)
//{
//	user->password= s;
// }
void Account::setmoney(double mm)
{
	this->money = mm;
}

int login(std::string _id, std::string _password)
{
	QString id = QString::fromStdString(_id);
	QString password = QString::fromStdString(_password);
	return db.CheckUser(id, password);
}

bool Account::is_oktobuy(double price)
{
	if (this->money < price) // ������������������ʱ��
	{
		return false;
	}
	else
	{
		return true;
	}
}
// Account* Account::Getaccount(bool is_ok)//���԰��Ǹ�enroll�ĺ���������������ж�
//{
//	if (is_ok)//���ɹ�ע���˺�
//	{
//		return acc.back();//��ȡ��ǰ�б��������˻�
//	}
//	else
//	{
//		return nullptr;
//	}
// }
std::string Account::get_name(Account *user)
{
	return user->Username;
}
std::vector<My_stock > Account::show_my_stock()
{
    mystock=db.getMyStock(this->id);
    return mystock;
}
int Account::add_my_order(int &operatorId, double price, int quantity, const QString &symbol, bool side)
{
	//-3 refer to the lack  of this sorts of stock
	//-2 refer to the sum of this stock is not enough
	//-1 refer to the lack of money to buy so much stocks
	//0 refer to  my stock is empty

	std::vector<My_stock > my = db.getMyStock(operatorId); // ��������һ�����������������������Կ�����ʲôӰ��
	if (!side)											// ���붩��
	{
		if (this->is_oktobuy(price * quantity)) // �Ƿ����㹻�Ľ��ȥ�ύ���붩��
		{
			//Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // �������붩��
            //std::cout << "����Ϊ����������" << std::endl;
			this->money -= price*quantity;//delete the money firstly
			db.updateUser(this->id, QString::fromStdString(this->Username), QString::fromStdString(this->password) , this->money);
			return db.addOrder(operatorId, price, quantity, symbol, side);
		}
		else
		{
            //std::cout << "����" << std::endl;
			//Order error = Order(); // �ն�������ʱ����ô�жϴ���
			return -1;
		}
	}
	else // ��������--ƥ���Լ��Ŀ���Ƿ��ж�Ӧ���ŵĹ�Ʊ�Ͷ�Ӧ�������Ĺ�Ʊ
	{
		if (my.empty()) // ����ҵĲֿ�Ϊ��
		{
            //std::cout << "�ֿ�Ϊ�գ��޷�����" << std::endl;
			return 0;
		}
		for (auto tem : my) // �����������
		{
			if (tem.get_name() == symbol.toStdString()) // �����Լ��Ŀ�����ҵ��˶�Ӧ�Ĺ�Ʊ����
			{
				if (quantity <= tem.get_sum()) // �����Լ���������㹻���ύ��������
				{
					//Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // ��������
					int Sum = tem.get_sum() - quantity;//new quantity of my stock
					tem.setnew_sum(Sum);
					this->mystock.assign(my.begin(), my.end());//local my_stock update
					db.updateUserStock(operatorId, symbol, Sum);//update myStock data
					return db.addOrder(operatorId, price, quantity, symbol, side);//Return the Order_id
				}
				else // ����й���������������ô�ඩ��
				{
                    //std::cout << "��������㣬�޷�����" << sum << "��������������������" << std::endl;
					//Order error = Order(); // �ն�������ʱ����ô�жϴ���
					return -2;
				}
			}
		}
        //std::cout << "��Ŀ����û�������Ʊ���޷�������������" << std::endl;
		return -3;
	}
}

void Account::upgrade(std::string _sym, int _sum, double price, Order&order) // ���¿����Ϣ,����ָ���ļ۸�
{
	if (!order.side) // �����������Ϣ
	{
		//this->money -= price;	   // ����Ҫ��Ǯ��--- Ǯ�Ѿ����ύ������ʱ�򽻹���
		if (this->mystock.empty()) // ����ֿ�Ϊ��
		{
			My_stock my_new(_sym, _sum);
			this->mystock.push_back(my_new); // ���µĹ�Ʊ��Ϣ�洢��������
			db.addUserStock(this->id, QString::fromStdString(_sym), QString::fromStdString(_sym), _sum);
		}
		else // ����ֿⲻΪ��
		{
			bool is_find = false; // �Ƿ��ҵ��и��ֹ�Ʊ
			for (auto tem : mystock)
			{
				if (tem.get_name() == _sym) // ���������������Ʊ���ͽ�������
				{
					tem.setnew_sum(tem.get_sum() + _sum); // �����µ�����
					is_find = true;
					db.updateUserStock(this->id, QString::fromStdString(_sym),tem.get_sum());
					break;
				}
			}
			// ��������û�����ֹ�Ʊ���Ǿ����ӽ�ȥ
			if (!is_find)
			{
				My_stock my_new(_sym, _sum);
				this->mystock.push_back(my_new); // ���µĹ�Ʊ��Ϣ�洢��������
				db.addUserStock(this->id, QString::fromStdString(_sym), QString::fromStdString(_sym), _sum);
			}
		}
	}
	else // �����������Ϣ,//֮ǰ�Ѿ��ж����ֿ�Ҫ�ж�Ӧ����������������������Ӧ��Ĭ�ϲֿ����ж�Ӧ�Ķ�����
	{
		for (auto tem : mystock)
		{
			if (_sym == tem.get_name()) // �ҵ��˲ֿ�Ŀ����
			{
				//tem->setnew_sum(tem->get_sum() - _sum); // ���¿�������---�����Ѿ��������������ύ������
				this->money += price;					// ׬Ǯ��
				db.updateUser(this->id, QString::fromStdString(this->Username), QString::fromStdString(this->password), this->money);
				break;
			}
		}
	}
}


int Account::removeOrder(int Orderid)
{
	std::vector<Order>myOrder = db.getMyOrdersList(this->return_id());//return User's Order list
	if (myOrder.empty())
	{
		return -1;
	}
	for (auto tem : myOrder)
	{
		if (tem.Order_id == Orderid)//use the orderid to find the correct order to remove
		{
			if (tem.side)//If it is a sell order
			{
				for (auto stock1 : this->mystock)
				{
					if (stock1.get_name() == tem.symbol)//find the stock
					{
						stock1.setnew_sum(tem.quantity+stock1.get_sum());
						db.updateUserStock(this->id, QString::fromStdString(tem.symbol),stock1.get_sum());
						if (db.removeOrder(Orderid))
							return Orderid;
						else
							return -1;
					}
				}
			}
			else//If it is a buy order
			{
				this->money += tem.price*tem.quantity;
				db.updateUser(this->id, QString::fromStdString(this->Username), QString::fromStdString(this->password), this->money);
				if (db.removeOrder(Orderid))
                    return Orderid;
				else
					return -1;
			}
		}
	}
}
std::vector<Order> Account::show_my_order()
{
    return db.getMyOrdersList(this->return_id());
}

int time(int duration, int id)//间隔时间，定位到第几号计时器
{
	static int srt[10];
	int end = clock();//统计程序运行到此处的时间 clock函数
	if (end - srt[id] > duration)  //duration 间隔时间
	{
		srt[id] = end;//开始时间改为上一次的结束时间
		return 1;//返回真
	}
	return 0;//返回假
}
