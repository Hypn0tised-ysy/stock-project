#pragma once
#include"Event.h"
#include<stdlib.h>
#include<cstdlib>
#include<time.h>
class Event_list
{
public:
	std::vector<Event*>event;//�洢���ߵ��б�
	void create_mylist();//����һ���¼��б�
	void choose(Stock&stock);//���ѡ��һ���¼�,����ָ���Ĺ�Ʊ���Ӱ��
	
};

