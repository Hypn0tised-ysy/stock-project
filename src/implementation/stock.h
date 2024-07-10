#pragma once
#include <vector>
#include <string>
#include "order_lk.h"
#include "Account.h"
#include "Account_group.h"
#include"order.h"
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
        price_list.push_back(p);
        name = n;
        databaseid=d;
    }
    Order_lk *orderlist_buy = new Order_lk(Order(-1, "0", -1, -1, "z", 0));
    Order_lk *orderlist_sell = new Order_lk(Order(-1, "0", -1, -1, "z", 1));
    std::vector<int> price_list;
    double highest_buy = 1.1, lowest_sell = 0.9;
    double lowest_buy = 0.95;  // 最低买入价格
    double higest_sell = 1.05; // 最高卖出价格

    void add_order(Order &order, Account_group &Ac); // ���Ӷ���,���ҵ������ݿ�
    void show_price()
    {
        for (int i = 0; i < price_list.size(); i++)
            std::cout << price_list[i] << " ";
    }
};
