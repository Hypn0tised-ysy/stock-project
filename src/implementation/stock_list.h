#pragma once
#include"stock.h"

class Stock_list {
private:
	//�洢��Ʊ
	std::vector<Stock>stk;
public:
	//��ӹ�Ʊ
	void add(std::string sym, int num, int origin);
	
	//��ʼ״̬����ʮֻ��Ʊ
	void origin();
};