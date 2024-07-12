#include"stock.h"

void Stock::add_order(Order &order) {
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
            //std::cout << "买入单不符合交易规则，订单已被退回。股票代码：" << symbol << " 订单号：" << order.Order_id << " 数量: "
                //<< order.quantity << " 价格:" << order.price << std::endl;
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
            //std::cout << "卖出单不符合交易规则，订单已被退回。股票代码：" << symbol << " 订单号：" << order.Order_id << " 数量: "
                //<< order.quantity << " 价格:" << order.price << std::endl;
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
               // std::cout << "成交：" << buyi->next->order.Order_id << " 股票代码：" << symbol << " 数量: " <<
                    //buyi->next->order.quantity << " 价格: " << selli->next->order.price << std::endl;
                //成交后订单生成可以在这里改。
                selli->next->order.quantity -= buyi->next->order.quantity;//剩余票数          
				db.updateOrder(selli->next->order.Order_id, selli->next->order.userid, selli->next->order.price, selli->next->order.quantity, QString::fromStdString(selli->next->order.symbol), selli->next->order.side);
				//Account*seller=Ac.find_user(selli->next->order.userid);//找到卖家id所指向的用户
				Account seller(selli->next->order.userid);
				seller.upgrade(selli->next->order.symbol, buyi->next->order.quantity, (buyi->next->order.quantity*selli->next->order.price),selli->next->order);
				//Account*buyer = Ac.find_user(buyi->next->order.userid);//找到买家id所指向的用户
				Account buyer(buyi->next->order.userid);
				buyer.upgrade(buyi->next->order.symbol, buyi->next->order.quantity,(buyi->next->order.quantity*selli->next->order.price), buyi->next->order);
				buyi->next->order.quantity = 0;//订单清空
				db.removeOrder(buyi->next->order.Order_id);//
				if (selli->next->order.quantity == 0)
				{
					db.removeOrder(selli->next->order.Order_id);
				}
            }
            else {//买量大于卖量
                //std::cout << "部分成交：" << buyi->next->order.Order_id << " 股票代码：" << symbol << " 数量: " <<
                   // selli->next->order.quantity << " 价格:" << selli->next->order.price << std::endl;
                buyi->next->order.quantity -= selli->next->order.quantity;
				db.updateOrder(buyi->next->order.Order_id, buyi->next->order.userid, buyi->next->order.price, buyi->next->order.quantity, QString::fromStdString(buyi->next->order.symbol), buyi->next->order.side);
				//Account*buyer = Ac.find_user(buyi->next->order.userid);//找到买家id所指向的用户
				Account buyer(buyi->next->order.userid);
				buyer.upgrade(buyi->next->order.symbol, selli->next->order.quantity, (selli->next->order.quantity*selli->next->order.price), buyi->next->order);
				Account seller(selli->next->order.userid);
				//Account*seller = Ac.find_user(selli->next->order.userid);//找到卖家id所指向的用户
				seller.upgrade(selli->next->order.symbol, selli->next->order.quantity, (selli->next->order.quantity*selli->next->order.price), selli->next->order);
                selli->next->order.quantity = 0;//clear the quantity
				db.removeOrder(selli->next->order.Order_id);//
            }
            market_price = selli->next->order.price; //更新股价！
        }
        else {
            buyi = buyi->next;
        }
        price_list.push_back(market_price);//这个列表存储了每次的股价，可以用来绘制图形？
    }
}
double Stock::show_price()//show the current price 
{
	if (price_list.empty())//if there is no order in this special time
	{
		if (Historic_price.empty())
			return market_price;//Return the lasttime;
		else
			return Historic_price.back();
	}
		
	else
	{
		double sum = std::accumulate(price_list.begin(), price_list.end(), 0.0);//get the Addsum
		double mean = sum / price_list.size();//get the mean
		market_price = mean;//update current price
		Historic_price.push_back(mean);//restore the mean
		price_list.clear();//reset the price list
		return mean;
	}

}