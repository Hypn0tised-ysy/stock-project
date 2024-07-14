#pragma once
#include <chrono>
#include <thread>
#include<cstdlib>
#include<ctime>
#include"Account.h"
#include"Event.h"
class Simulated_user : public Account {

public:
Simulated_user(){};
Simulated_user(int _id);
 // 模拟用户进行交易
void s_trade(double _price,int _quantity,QString &_symbol,bool side);

};
//创建模拟用户
void create_s_acc();

//模拟交易
void simulated_trade();




