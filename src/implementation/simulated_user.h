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
 // ģ���û����н���
void s_trade(double _price,int _quantity,QString &_symbol,bool side);

};
//����ģ���û�
void create_s_acc();

//ģ�⽻��
void simulated_trade();




