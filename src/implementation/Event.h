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
	std::string name;//�¼�����
	bool good_or_bad;//�¼��ĺû�//����true������false
	void impact(Stock &stock);//���߻������¼���Ӱ��
	Event(std::string _name,bool gob);
	Event();
};

