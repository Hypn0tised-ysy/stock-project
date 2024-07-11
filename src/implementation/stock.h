#pragma once
#include <vector>
#include <string>
#include "order_lk.h"
#include "Account.h"
#include "Account_group.h"
#include"order.h"
#include <algorithm>
#include <numeric>
class Stock
{
public:
    std::string symbol;  // ��Ʊ����
    double market_price; // ��ǰ�ɼ�
    std::string name;
    int databaseid;
    Stock(std::string s, double p,std::string n,int d)
    { // ��ʼ�ɼۿ�������������
        symbol = s;
        market_price = p;
        //price_list.push_back(p);
        name = n;
        databaseid=d;
    }
    Order_lk *orderlist_buy = new Order_lk(Order(-1, "0", -1, -1, "z", 0));
    Order_lk *orderlist_sell = new Order_lk(Order(-1, "0", -1, -1, "z", 1));
    std::vector<double> price_list;//current trade price
	
	std::vector<double> Historic_price;//historic price list
    double highest_buy = 1.1, lowest_sell = 0.9;
    double lowest_buy = 0.95;  // 最低买入价格
    double higest_sell = 1.05; // 最高卖出价格
	
    void add_order(Order &order); // ���Ӷ���,���ҵ������ݿ�
	double show_price();//Return current market_price
};
