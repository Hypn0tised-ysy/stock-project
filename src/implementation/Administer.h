#pragma once
#include<vector>
#include<string>
#include"stock.h"
#include<Qstring>
class Administer
{
public://全部设置共有成员，便于调用查看
	int adminId;//管理员的id
	std::string aminName;//管理员的账号
	std::string password;//管理员的密码
	std::vector<Stock>stocklist;//本地存储股票的数组
	bool addStock(std::string symbol,std::string name,double price);//管理员添加股票,参数为股票代号和该种股票的初始价格
	bool removeStock(int stockId,std::string symbol);//管理员删除股票信息,从数据库中删除
	Administer();//
	Administer(int id, std::string name, std::string password);//带默认形参的构造函数
	std::vector<Stock> getStock();//管理员有权获取当前市场的股票列表
};

