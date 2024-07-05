#include<iostream>
#include<cmath>
#include<vector>
#include<string>
#include<algorithm>

struct Order {    //ԭʼ����
    int Order_id; //�����ţ�Ψһ��־��
    int Peo_id;   //������id
    double price;    //����۸�
    int quantity; //��������
    bool side;    //�������򣬼���0Ϊ���붩����1Ϊ�������������Ը�
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
    std::string symbol;  //��Ʊ����
    double market_price;  //��ǰ�ɼ�
    Stock(std::string s, double p) {  //��ʼ�ɼۿ�������������
        symbol = s; market_price = p;
        price_list.push_back(p);
    }
    Order_lk* orderlist_buy = new Order_lk(Order(-1, -1, -1, -1, 0));
    Order_lk* orderlist_sell = new Order_lk(Order(-1, -1, -1, -1, 1));
    std::vector<int>price_list;
    double highest_buy = 1.1, lowest_sell = 0.9;
    void add_order(Order order); //��Ӷ���
    void show_price() {
        for (int i = 0; i < price_list.size(); i++)
            std::cout << price_list[i] << " ";
    }
};

void Stock::add_order(Order order) {
    Order_lk* p=new Order_lk(order);
    if (!order.side) {
        if (order.price <= market_price * highest_buy) {  //�۸�Ϲ�
            if (orderlist_buy->next == NULL)
                orderlist_buy->next = p;
            else {
                Order_lk* q = orderlist_buy;     //ʵ����۵ĴӴ�С����
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
            std::cout << "���뵥�����Ͻ��׹��򣬶����ѱ��˻ء���Ʊ���룺"<< symbol <<" �����ţ�" << order.Order_id << " ����: "
                << order.quantity << " �۸�:" << order.price << std::endl;
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
            std::cout << "�����������Ͻ��׹��򣬶����ѱ��˻ء���Ʊ���룺" << symbol << " �����ţ�" << order.Order_id << " ����: "
                << order.quantity << " �۸�:" << order.price << std::endl;
        }
    }
    //���ݼ۸�����ԭ���ϳɽ�
    Order_lk* buyi = orderlist_buy;
    Order_lk* selli = orderlist_sell;
    Order_lk* delete_node;
    while (buyi->next != NULL && selli->next != NULL) {
        if (buyi->next->order.quantity == 0) {  //��������Ϊ0�Ķ�����ʵ����Ҫɾ��!!!!!!!
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
        if (buyi->next->order.price >= selli->next->order.price) {  //�ɽ�
            if (buyi->next->order.quantity <= selli->next->order.quantity) {
                std::cout << "�ɽ���" << buyi->next->order.Order_id << " ��Ʊ���룺"<< symbol << " ����: " <<
                    buyi->next->order.quantity << " �۸�: " << selli->next->order.price << std::endl;
                //�ɽ��󶩵����ɿ���������ġ�
                selli->next->order.quantity -= buyi->next->order.quantity;
                buyi->next->order.quantity = 0;
            }
            else {
                std::cout << "���ֳɽ���" << buyi->next->order.Order_id << " ��Ʊ���룺" << symbol << " ����: " <<
                    selli->next->order.quantity << " �۸�:" << selli->next->order.price << std::endl;
                buyi->next->order.quantity -= selli->next->order.quantity;
                selli->next->order.quantity = 0;
            }
            market_price = selli->next->order.price; //���¹ɼۣ�
        }
        else {
            buyi = buyi->next;
        }
        price_list.push_back(market_price);
    }
}