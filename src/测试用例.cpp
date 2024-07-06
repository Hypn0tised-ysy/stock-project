#include<iostream>
#include<string>
#include<math.h>
#include<fstream>
#include<stack>
#include<vector>
#include<conio.h>
//#include"Account.h"
#include"stock.h"
#include"Account_group.h"
using namespace std;
Account_group Ac;//创建一个总账户存储的一个集合实现
int main()
{
	cout << "Please begin enroll your account"<<endl;
	std::string id;
	std::string password;
	cin >> id >> password;
	Account*p1 = Ac.Getaccount(Ac.enroll(id, password));

	//////
	std::string id1;
	std::string password1;
	cin >> id1 >> password1;
	Account*p2 = Ac.Getaccount(Ac.enroll(id1, password1));
	/////
	Stock stock("A", 100);
	Order o1=add_my_order(1, p1, 99, 100, "A", 1);//卖家
	stock.add_order(o1, Ac);
	Order o2 = add_my_order(2, p2, 100, 100, "A", 0);
	stock.add_order(o2, Ac);
	stock.show_price();
	return 0;
}