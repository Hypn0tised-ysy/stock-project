#include "Administer.h"
#include "../database/database.h"
#include <QVariantList>
extern Database db;
bool Administer::addStock(std::string symbol,std::string name, double price)//管理员添加股票,股票代号和股价
{
	std::vector<Stock> tem = db.getStocksList();
	this->stocklist.assign(tem.begin(), tem.end());//将本地的股票数据更新
	if (stocklist.empty())//如果仓库为空,则直接添加股票
	{
		Stock stock(symbol, price);
		this->stocklist.push_back(stock);
		return db.addStock(QString::fromStdString(symbol), QString::fromStdString(name), price);
	}
	else//如果仓库不为空
	{
		for (auto tem1 : stocklist)
		{
			if (tem1.symbol == symbol)//如果添加的股票市场已经存在的话，那么无法进行添加操作
			{
				return false;
			}
		}
		//反之，市场中不存在这种股票,则添加进入股票的list中 
		Stock stock(symbol, price);
		this->stocklist.push_back(stock);
		return db.addStock(QString::fromStdString(symbol), QString::fromStdString(name), price);
	}
	
	
}
bool Administer::removeStock(int stockId,std::string symbol)
{
	std::vector<Stock> tem = db.getStocksList();
	this->stocklist.assign(tem.begin(), tem.end());//将本地的股票数据更新
	if (this->stocklist.empty())//市场没有股票，则无法进行删除操作
	{
		return false;
	}
	else//股票市场存在股票，进行查找
	{
		for (auto tem1 : stocklist)
		{
			if (tem1.symbol == symbol)//找到了
			{
				return db.removeStock(stockId);
			}			
		}
		return false;//没有找到
	}
	 
}
Administer::Administer()
{

}
Administer::Administer(int id=1, std::string name="110", std::string pass="119")// 本地初始化
{
	this->adminId = id;
	this->aminName = name;
	this->password = pass;
}
std::vector<Stock> Administer::getStock()//管理员有权限获取当前市场所有存在的股票
{
	std::vector<Stock> tem= db.getStocksList();
	this->stocklist.assign(tem.begin(), tem.end());//将本地的股票数据更新
	return db.getStocksList();
}