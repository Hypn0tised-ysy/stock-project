#pragma once
#include"stock.h"

class Stock_list {
private:
	//存储股票
	std::vector<Stock>stk;
public:
	//添加股票
	void add(std::string sym, int num, int origin);
	
	//初始状态上市十只股票
	void origin();
};