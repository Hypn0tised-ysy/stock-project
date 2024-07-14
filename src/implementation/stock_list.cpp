#include"stock_list.h"

//添加股票种类
void Stock_list::add(std::string sym, int num, int fund) {
	double oringin_price = fund / num;
	Stock s(sym, oringin_price);
	stk.push_back(s);
};




//初始状态股票
void Stock_list::origin() {
	for (int i = 0; i < 9; i++)
	{
		std::string sym = "stock" + std::to_string(i);
		int fund = (rand() % 9 + 1) * 1000000;
		int num = 1000000;
		add(sym, num, fund);
	}
}