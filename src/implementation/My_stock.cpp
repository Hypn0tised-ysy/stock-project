#include "My_stock.h"
int My_stock::get_sum()
{
	return sum;
}
std::string My_stock::get_name()
{
	return symbol;
}
void My_stock::setnew_sum(int _sum)
{
	this->sum = _sum;
}
My_stock::My_stock(std::string _symbol="A", int _sum=100)
{
	this->symbol = _symbol;
	this->sum = _sum;
}