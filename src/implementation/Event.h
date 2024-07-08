#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include"stock.h"

class Event
{
public:
	std::string name;//事件名称
	bool good_or_bad;//事件的好坏//好是true，坏是false
	void impact(Stock &stock);//政策或者是事件的影响
	Event(std::string _name,bool gob);
	Event();
};

