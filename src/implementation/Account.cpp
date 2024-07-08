#include "Account.h"
#include"database.h"
Account::Account(std::string _id, std::string _password, double _money)
{
	id = _id;
	//password = _password;
	//money = _money;
}


int enroll(std::string _id,std::string _password)
{

	return db.addUser(_id, _password, 50000);
}





//void Account::setid(Account *user,bool &reg,std::string s)
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
//}




//void Account::setpassword(Account *user,std::string s)
//{
//	user->password= s;
//}
void Account::setmoney(double mm)
{
	this->money = mm;
}




int login(std::string _id, std::string _password)
{
	
	return db.CheckUser(_id, _password);

}




bool Account::check(std::string id, std::string pass)
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


bool Account::is_oktobuy(double price,Account *user)
{
	if (user->money < price)//当订单需求满足余额的时候
	{
		return false;
	}
	else
	{
		return true;
	}
}
//Account* Account::Getaccount(bool is_ok)//可以把那个enroll的函数放在这里进行判定
//{
//	if (is_ok)//当成功注册账号
//	{
//		return acc.back();//获取当前列表的最新账户
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
	
	std::vector<My_stock*>my = user->show_my_stock();//本质上是一个副本，更改这个副本不会对库存造成什么影响
	if (!side)//买入订单
	{
		if (user->is_oktobuy(price*sum, user))//是否有足够的金额去提交买入订单
		{
			Order  mynew =Order(order_id, user->get_id(user), price, sum, sym, side);//创建买入订单
			std::cout << "正在为您创建订单" << std::endl;
			return mynew;
		}
		else
		{
			std::cout << "余额不足" << std::endl;
			Order  error = Order();//空订单，到时候看怎么判断错误
			return error;
		}
	}
	else//卖出订单--匹配自己的库存是否有对应代号的股票和对应的数量的股票
	{
		if (my.empty())//如果我的仓库为空
		{
			std::cout << "仓库为空，无法交易" << std::endl;
			Order  error = Order();//创建买入订单
			return error;
		}
		for (auto tem : my)//遍历整个库存
		{
			if (tem->get_name() == sym)//当在自己的库存中找到了对应的股票代码
			{
				if (sum <= tem->get_sum())//并且自己库存量还足够，提交卖出订单
				{
					Order mynew =  Order(order_id, user->get_id(user), price, sum, sym, side);//创建订单
					return mynew;
				}
				else//库存中股数不足以卖出这么多订单
				{
					std::cout << "库存量不足，无法卖出" << sum << "个订单，请重新再输入" << std::endl;
					Order  error = Order();//空订单，到时候看怎么判断错误
					return error;
				}
			}
			
		}
		std::cout << "你的库存里没有这类股票，无法进行卖出交易" << std::endl;
		Order  error = Order();//空订单，到时候看怎么判断错误
		return error;
	}
	
}
Account*Account::find_user(std::string _id)//找到对应id的用户
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



void Account::upgrade(std::string _sym, int _sum, double price, Order&order)//更新库存信息,根据指定的价格
{
	if (!order.side)//如果是买入信息
	{
		this->money -= price;//买东西要交钱的  
		if (this -> mystock.empty())//如果仓库为空
		{
			My_stock*my_new = new My_stock(_sym, _sum);
			this->mystock.push_back(my_new);//将新的股票信息存储进入库存中
		}
		else//如果仓库不为空
		{
			bool is_find = false;//是否找到有该种股票
			for (auto tem : mystock)
			{
				if (tem->get_name() == _sym)//如果库存中有这个股票，就进行增加
				{
					tem->setnew_sum(tem->get_sum() + _sum);//设置新的数量
					is_find = true;
					break;
				}
			}
			//如果库存中没有这种股票，那就添加进去
			if (!is_find)
			{
				My_stock*my_new = new My_stock(_sym, _sum);
				this->mystock.push_back(my_new);//将新的股票信息存储进入库存中
			}
			
		}
		
	}
	else//如果是卖出信息,//之前已经判定过仓库要有对应东西才能卖出，所以这里应该默认仓库是有对应的东西的
	{
		for (auto tem : mystock)
		{
			if (_sym == tem->get_name())//找到了仓库的库存了
			{
				tem->setnew_sum(tem->get_sum() - _sum);//更新库存的数量
				this->money += price;//赚钱了
				break;
			}
		}
	}
}

//注释部分为第一版曾经用过的实现方式，现在添加了Account_group来存储账户信息，看起来更好看了