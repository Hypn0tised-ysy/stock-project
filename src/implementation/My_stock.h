#pragma once
#include<string>
class My_stock//库存仓库，用于存储股票信息
{
private:
	std::string symbol;//股票代号
	int sum;//股票数量
public:
	int get_sum();//获取当前股票类型的拥有量
	std::string get_name();//获取当前的股票代号
	void setnew_sum(int _sum);//设置新的数量
	My_stock(const std::string _symbol,const int _sum);
};

