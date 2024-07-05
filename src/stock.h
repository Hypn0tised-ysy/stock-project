#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>

struct Order {    //原始订单
    int Order_id; //订单号（唯一标志）
    int Peo_id;   //操作者id
    double price;    //意向价格
    int quantity; //意向数量
    bool side;    //买卖方向，假设0为买入订单，1为卖出订单，可以改
    Order(int oid = 0, int pid = 0, double p = 0, int q = 0, bool s = 0) {
        Order_id = oid; Peo_id = pid; side = s; price = p; quantity = q;
    }
    Order(const Order& o) {
        Order_id = o.Order_id; Peo_id = o.Peo_id; side = o.side; price = o.price; quantity = o.quantity;
    }
    bool operator==(const Order& o) {
        return Order_id == o.Order_id;
    }
};

struct Order_lk {
    Order order;
    Order_lk* next;
    Order_lk() { next = NULL; }
    Order_lk(Order o) { order = o; next = NULL; }
    Order_lk(const Order_lk& o) {
        order = o.order; next = o.next;
    }
};

class Stock {
public:
    std::string symbol;  //股票代码
    double market_price;  //当前股价
    Stock(std::string s, double p) {  //初始股价可以在这里设置
        symbol = s; market_price = p;
        price_list.push_back(p);
    }
    Order_lk* orderlist_buy = new Order_lk(Order(-1, -1, -1, -1, 0));
    Order_lk* orderlist_sell = new Order_lk(Order(-1, -1, -1, -1, 1));
    std::vector<int>price_list;
    double highest_buy = 1.1, lowest_sell = 0.9;
    void add_order(Order order); //添加订单
    void show_price() {
        for (int i = 0; i < price_list.size(); i++)
            std::cout << price_list[i] << " ";
    }
};

void Stock::add_order(Order order) {
    Order_lk* p=new Order_lk(order);
    if (!order.side) {
        if (order.price <= market_price * highest_buy) {  //价格合规
            if (orderlist_buy->next == NULL)
                orderlist_buy->next = p;
            else {
                Order_lk* q = orderlist_buy;     //实现买价的从大到小排序
                while (q->next != NULL && q->next->order.price >= p->order.price)
                    q = q->next;
                if (q->next == NULL) {
                    q->next = p;
                    p->next = NULL;
                }
                else {
                    p->next = q->next;
                    q->next = p;
                }
            }
        }
        else {
            std::cout << "买入单不符合交易规则，订单已被退回。股票代码："<< symbol <<" 订单号：" << order.Order_id << " 数量: "
                << order.quantity << " 价格:" << order.price << std::endl;
        }
    }
    else {
        if (order.price >= market_price * lowest_sell) {
            if (orderlist_sell->next == NULL)
                orderlist_sell->next = p;
            else {
                Order_lk* q = orderlist_sell;
                while (q->next != NULL && q->next->order.price <= p->order.price)
                    q = q->next;
                if (q->next == NULL) {
                    q->next = p;
                    p->next = NULL;
                }
                else {
                    p->next = q->next;
                    q->next = p;
                }
            }
        }
        else {
            std::cout << "卖出单不符合交易规则，订单已被退回。股票代码：" << symbol << " 订单号：" << order.Order_id << " 数量: "
                << order.quantity << " 价格:" << order.price << std::endl;
        }
    }
    //根据价格优先原则撮合成交
    Order_lk* buyi = orderlist_buy;
    Order_lk* selli = orderlist_sell;
    Order_lk* delete_node;
    while (buyi->next != NULL && selli->next != NULL) {
        if (buyi->next->order.quantity == 0) {  //跳过数量为0的订单，实际上要删除!!!!!!!
            if (buyi->next->next != NULL)
                buyi = buyi->next;
            else
                break;
        }
        if (selli->next->order.quantity == 0) {
            if (selli->next->next != NULL)
                selli = selli->next;
            else
                break;
        }
        if (buyi->next->order.price >= selli->next->order.price) {  //成交
            if (buyi->next->order.quantity <= selli->next->order.quantity) {
                std::cout << "成交：" << buyi->next->order.Order_id << " 股票代码："<< symbol << " 数量: " <<
                    buyi->next->order.quantity << " 价格: " << selli->next->order.price << std::endl;
                //成交后订单生成可以在这里改。
                selli->next->order.quantity -= buyi->next->order.quantity;
                buyi->next->order.quantity = 0;
            }
            else {
                std::cout << "部分成交：" << buyi->next->order.Order_id << " 股票代码：" << symbol << " 数量: " <<
                    selli->next->order.quantity << " 价格:" << selli->next->order.price << std::endl;
                buyi->next->order.quantity -= selli->next->order.quantity;
                selli->next->order.quantity = 0;
            }
            market_price = selli->next->order.price; //更新股价！
        }
        else {
            buyi = buyi->next;
        }
        price_list.push_back(market_price);
    }
}