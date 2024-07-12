#pragma once
#include<string>
struct Order {    //原始订单
    int Order_id; //订单号（唯一标志）
    std::string Peo_id;   //操作者id
    double price;    //意向价格
    int quantity; //意向数量
	std::string symbol;//股票的类型
    int userid;//
    bool side;    //买卖方向，假设0为买入订单，1为卖出订单，可以改
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
