#pragma once
#include <chrono>
#include <thread>
#include<cstdlib>
#include<ctime>
#include"Account.h"
#include"Event.h"
class Simulated_user : public Account {
private:
    int id;							  
    std::string Username;			 
    std::string password;			 
    double money;					 
    std::vector<My_stock> mystock;
public:
    //创建模拟用户
    void create_s_acc();
  
    //模拟交易
    void simulated_trade();

};







