#pragma once
#include<iostream>
#include <chrono>
#include <thread>
#include<cstdlib>
#include<ctime>
#include"Account.h"
#include"My_stock"
class Simulated_user : public Account {
;
public:

    Simulated_user(std::string _id, double _money);
    //����ģ���û�
    void create_s_acc();
   
    
    //ģ�⽻��
    void simulated_trade();

    //���¹�Ʊ��Ϣ
    void upgrade(std::string _sym, int _sum, double price, Order& order);

   


    
};




Order add_my_order(int order_id, Simulated_user* user, double price, int sum, std::string sym, bool side);


