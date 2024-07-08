#include "Event_list.h"

void Event_list::create_mylist()
{
	std::ifstream my;
	my.open("event.txt");
	std::string eva;
	while (getline(my, eva))
	{
		std::string tem;
		std::stringstream ss(eva);
		int i = 0;
		Event*newevent = new Event();
		while (ss >> tem)
		{
			if (i == 0)
			{
				newevent->name = tem;
				
				i++;
			}
			else
			{
				if (tem == "T")
				{
					newevent->good_or_bad = true;
					event.push_back(newevent);
				}
				else
				{
					newevent->good_or_bad = false;
					event.push_back(newevent);
				}
			}
			
		}
	}

	my.close();
}

void Event_list::choose(Stock&stock)//随机选择一个事件
{
	
	int cho = (rand() % 12);
	std::cout << event[cho]->name << std::endl;
	event[cho]->impact(stock);
}
