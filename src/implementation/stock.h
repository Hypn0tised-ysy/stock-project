#pragma once
#include<vector>
#include<string>
#include"order_lk.h"
#include "Account.h"
#include"Account_group.h"
class Stock {
public:
    std::string symbol;  //��Ʊ����
    double market_price;  //��ǰ�ɼ�
    Stock(std::string s, double p) {  //��ʼ�ɼۿ�������������
        symbol = s; market_price = p;
        price_list.push_back(p);
    }
    Order_lk* orderlist_buy = new Order_lk(Order(-1, "0", -1, -1,"z", 0));
    Order_lk* orderlist_sell = new Order_lk(Order(-1, "0", -1, -1,"z", 1));
    std::vector<int>price_list;
    double highest_buy = 1.1, lowest_sell = 0.9;
    void add_order(Order &order, Account_group &Ac); //��Ӷ���,���ҵ������ݿ�
    void show_price() {
        for (int i = 0; i < price_list.size(); i++)
            std::cout << price_list[i] << " ";
    }
};

