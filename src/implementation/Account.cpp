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
//	if (acc.empty())//如果账号数据存储中没有账号信息，则
//	{
//		user->id = s;
//		reg = false;
//	}
//
//	else
//	{
//		for (auto t : acc)//遍历账户的数据存储库
//		{
//			if (s == t->id)//当你输入的账号信息与数据库中存在的信息有重复的时候
//			{
//				std::cout << "somebody use this id,Please try another one" << std::endl;
//				reg = true;//重新输一遍
//				return;
//			}
//		}
//		user->id = s;//注册信息通过要求，可以注册
//
//		reg = false;//更改判定条件
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
	if (this->money < price) // 当订单需求满足余额的时候
	{
		return false;
	}
	else
	{
		return true;
	}
}
// Account* Account::Getaccount(bool is_ok)//可以把那个enroll的函数放在这里进行判定
//{
//	if (is_ok)//当成功注册账号
//	{
//		return acc.back();//获取当前列表的最新账户
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
	return mystock;
}
int Account::add_my_order(int &operatorId, double price, int quantity, const QString &symbol, bool side)
{
	//-3 refer to the lack  of this sorts of stock
	//-2 refer to the sum of this stock is not enough
	//-1 refer to the lack of money to buy so much stocks
	//0 refer to  my stock is empty

	std::vector<My_stock > my = db.getMyStock(operatorId); // 本质上是一个副本，更改这个副本不会对库存造成什么影响
	if (!side)											// 买入订单
	{
		if (this->is_oktobuy(price * quantity)) // 是否有足够的金额去提交买入订单
		{
			//Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // 创建买入订单
            //std::cout << "正在为您创建订单" << std::endl;
			this->money -= price*quantity;//delete the money firstly

			return db.addOrder(operatorId, price, quantity, symbol, side);
		}
		else
		{
            //std::cout << "余额不足" << std::endl;
			//Order error = Order(); // 空订单，到时候看怎么判断错误
			return -1;
		}
	}
	else // 卖出订单--匹配自己的库存是否有对应代号的股票和对应的数量的股票
	{
		if (my.empty()) // 如果我的仓库为空
		{
            //std::cout << "仓库为空，无法交易" << std::endl;
			return 0;
		}
		for (auto tem : my) // 遍历整个库存
		{
			if (tem.get_name() == symbol.toStdString()) // 当在自己的库存中找到了对应的股票代码
			{
				if (quantity <= tem.get_sum()) // 并且自己库存量还足够，提交卖出订单
				{
					//Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // 创建订单
					int Sum = tem.get_sum() - quantity;//new quantity of my stock
					tem.setnew_sum(Sum);
                    this->mystock.assign(my.begin(), my.end());//local my_stock update
					db.updateUserStock(operatorId, symbol, Sum);//update myStock data
					return db.addOrder(operatorId, price, quantity, symbol, side);//Return the Order_id
				}
				else // 库存中股数不足以卖出这么多订单
				{
                    //std::cout << "库存量不足，无法卖出" << sum << "个订单，请重新再输入" << std::endl;
					//Order error = Order(); // 空订单，到时候看怎么判断错误
					return -2;
				}
			}
		}
        //std::cout << "你的库存里没有这类股票，无法进行卖出交易" << std::endl;
		return -3;
	}
}

void Account::upgrade(std::string _sym, int _sum, double price, Order&order) // 更新库存信息,根据指定的价格
{
	if (!order.side) // 如果是买入信息
	{
		//this->money -= price;	   // 买东西要交钱的--- 钱已经在提交订单的时候交过了
		if (this->mystock.empty()) // 如果仓库为空
		{
			My_stock my_new(_sym, _sum);
			this->mystock.push_back(my_new); // 将新的股票信息存储进入库存中
		}
		else // 如果仓库不为空
		{
			bool is_find = false; // 是否找到有该种股票
			for (auto tem : mystock)
			{
				if (tem.get_name() == _sym) // 如果库存中有这个股票，就进行增加
				{
					tem.setnew_sum(tem.get_sum() + _sum); // 设置新的数量
					is_find = true;
					break;
				}
			}
			// 如果库存中没有这种股票，那就添加进去
			if (!is_find)
			{
				My_stock my_new(_sym, _sum);
				this->mystock.push_back(my_new); // 将新的股票信息存储进入库存中
			}
		}
	}
	else // 如果是卖出信息,//之前已经判定过仓库要有对应东西才能卖出，所以这里应该默认仓库是有对应的东西的
	{
		for (auto tem : mystock)
		{
			if (_sym == tem.get_name()) // 找到了仓库的库存了
			{
				//tem->setnew_sum(tem->get_sum() - _sum); // 更新库存的数量---数量已经在卖出订单的提交更新了
				this->money += price;					// 赚钱了
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
