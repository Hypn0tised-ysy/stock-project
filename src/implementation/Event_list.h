#pragma once
#include"Event.h"
#include<stdlib.h>
#include<cstdlib>
#include<time.h>
class Event_list
{
public:
	std::vector<Event*>event;//存储政策的列表，
	void create_mylist();//创建一个事件列表
	void choose(Stock&stock);//随机选择一个事件,并对指定的股票造成影响
	
};

