#pragma once
#include<string>
#include<vector>
#include<iostream>
using namespace std;
class Event
{
public:
	string name;//事件名称
	vector<Event>event;
	void impact();//政策或者是事件的影响

};

