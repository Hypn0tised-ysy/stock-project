#pragma once
#include<string>
struct Order {    //ԭʼ����
    int Order_id; //�����ţ�Ψһ��־��
    std::string Peo_id;   //������id
    double price;    //����۸�
    int quantity; //��������
	std::string symbol;//��Ʊ������
    int userid;//
    bool side;    //�������򣬼���0Ϊ���붩����1Ϊ�������������Ը�
    Order(int oid = 0, std::string pid = "0", double p = 0, int q = 0, std::string sym="Z",bool s=false ) {
        Order_id = oid; Peo_id = pid; side = s; price = p; quantity = q; symbol = sym;
    }
    Order(const Order& o) {
		Order_id = o.Order_id; Peo_id = o.Peo_id; side = o.side; price = o.price; quantity = o.quantity; symbol = o.symbol;
        userid=o.userid;
    }
    bool operator==(const Order& o) {
        return Order_id == o.Order_id;
    }
};
