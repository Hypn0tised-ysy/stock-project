#include "Event.h"
void Event::impact(Stock &stock)
{
	if (good_or_bad)//����Ǻ��¼�
	{
		stock.market_price *= 1.02;
		stock.price_list.push_back(stock.market_price);
	}
	else//�����¼�
	{
		stock.market_price *= 0.99;
		stock.price_list.push_back(stock.market_price);
	}
}
Event::Event(std::string _name, bool gob)
{
	name = _name;
	good_or_bad = gob;
}
Event::Event()
{

}