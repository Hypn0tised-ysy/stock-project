#include "Event.h"
void Event::impact(Stock &stock)
{
	if (good_or_bad)//如果是好事件
	{
		if(stock.lowest_buy<=0.99)
			stock.lowest_buy += 0.01;
	}
	else//消极事件
	{
		if(stock.higest_sell>=1.01)
			stock.higest_sell -= 0.01;
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