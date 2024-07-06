#include"stock.h"

void Stock::add_order(Order &order,Account_group &Ac) {
    Order_lk* p = new Order_lk(order);
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
            std::cout << "买入单不符合交易规则，订单已被退回。股票代码：" << symbol << " 订单号：" << order.Order_id << " 数量: "
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
        if (buyi->next->order.quantity == 0) {  //跳过并删除数量为0的订单
            delete_node = buyi->next;
            if (delete_node->next != NULL) {
                buyi->next = delete_node->next;
                delete(delete_node);
            }
            else {
                buyi->next = NULL;
                delete(delete_node);
                break;
            }
        }
        if (selli->next->order.quantity == 0) {
            delete_node = selli->next;
            if (delete_node->next != NULL) {
                selli->next = delete_node->next;
                delete(delete_node);
            }
            else {
                selli->next = NULL;
                delete(delete_node);
                break;
            }
        }
        if (buyi->next->order.price >= selli->next->order.price) {  //成交
            if (buyi->next->order.quantity <= selli->next->order.quantity) //买量小于等于卖量
			{
                std::cout << "成交：" << buyi->next->order.Order_id << " 股票代码：" << symbol << " 数量: " <<
                    buyi->next->order.quantity << " 价格: " << selli->next->order.price << std::endl;
                //成交后订单生成可以在这里改。
                selli->next->order.quantity -= buyi->next->order.quantity;//剩余票数               
				Account*seller=Ac.find_user(selli->next->order.Peo_id);//找到卖家id所指向的用户
				seller->upgrade(selli->next->order.symbol, buyi->next->order.quantity, (buyi->next->order.quantity*selli->next->order.price),selli->next->order);
				Account*buyer = Ac.find_user(buyi->next->order.Peo_id);//找到买家id所指向的用户
				buyer->upgrade(buyi->next->order.symbol, buyi->next->order.quantity,(buyi->next->order.quantity*selli->next->order.price), buyi->next->order);
				buyi->next->order.quantity = 0;//订单清空
            }
            else {//买量大于卖量
                std::cout << "部分成交：" << buyi->next->order.Order_id << " 股票代码：" << symbol << " 数量: " <<
                    selli->next->order.quantity << " 价格:" << selli->next->order.price << std::endl;
                buyi->next->order.quantity -= selli->next->order.quantity;
				Account*buyer = Ac.find_user(buyi->next->order.Peo_id);//找到买家id所指向的用户
				buyer->upgrade(buyi->next->order.symbol, selli->next->order.quantity, (selli->next->order.quantity*selli->next->order.price), buyi->next->order);

				Account*seller = Ac.find_user(selli->next->order.Peo_id);//找到卖家id所指向的用户
				seller->upgrade(selli->next->order.symbol, selli->next->order.quantity, (selli->next->order.quantity*selli->next->order.price), selli->next->order);
                selli->next->order.quantity = 0;
            }
            market_price = selli->next->order.price; //更新股价！
        }
        else {
            buyi = buyi->next;
        }
        price_list.push_back(market_price);//这个列表存储了历史的股价，可以用来绘制图形？
    }
}
