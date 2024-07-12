#include"stock.h"

void Stock::add_order(Order &order) {
    Order_lk* p = new Order_lk(order);
	
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
            //std::cout << "���뵥�����Ͻ��׹��򣬶����ѱ��˻ء���Ʊ���룺" << symbol << " �����ţ�" << order.Order_id << " ����: "
                //<< order.quantity << " �۸�:" << order.price << std::endl;
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
            //std::cout << "�����������Ͻ��׹��򣬶����ѱ��˻ء���Ʊ���룺" << symbol << " �����ţ�" << order.Order_id << " ����: "
                //<< order.quantity << " �۸�:" << order.price << std::endl;
        }
    }
    //���ݼ۸�����ԭ���ϳɽ�
    Order_lk* buyi = orderlist_buy;
    Order_lk* selli = orderlist_sell;
    Order_lk* delete_node;
    while (buyi->next != NULL && selli->next != NULL) {
        if (buyi->next->order.quantity == 0) {  //������ɾ������Ϊ0�Ķ���
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
        if (buyi->next->order.price >= selli->next->order.price) {  //�ɽ�
            if (buyi->next->order.quantity <= selli->next->order.quantity) //����С�ڵ�������
			{
               // std::cout << "�ɽ���" << buyi->next->order.Order_id << " ��Ʊ���룺" << symbol << " ����: " <<
                    //buyi->next->order.quantity << " �۸�: " << selli->next->order.price << std::endl;
                //�ɽ��󶩵����ɿ���������ġ�
                selli->next->order.quantity -= buyi->next->order.quantity;//ʣ��Ʊ��          
				db.updateOrder(selli->next->order.Order_id, selli->next->order.userid, selli->next->order.price, selli->next->order.quantity, QString::fromStdString(selli->next->order.symbol), selli->next->order.side);
				//Account*seller=Ac.find_user(selli->next->order.userid);//�ҵ�����id��ָ����û�
				Account seller(selli->next->order.userid);
				seller.upgrade(selli->next->order.symbol, buyi->next->order.quantity, (buyi->next->order.quantity*selli->next->order.price),selli->next->order);
				//Account*buyer = Ac.find_user(buyi->next->order.userid);//�ҵ����id��ָ����û�
				Account buyer(buyi->next->order.userid);
				buyer.upgrade(buyi->next->order.symbol, buyi->next->order.quantity,(buyi->next->order.quantity*selli->next->order.price), buyi->next->order);
				buyi->next->order.quantity = 0;//�������
				db.removeOrder(buyi->next->order.Order_id);//
				if (selli->next->order.quantity == 0)
				{
					db.removeOrder(selli->next->order.Order_id);
				}
            }
            else {//������������
                //std::cout << "���ֳɽ���" << buyi->next->order.Order_id << " ��Ʊ���룺" << symbol << " ����: " <<
                   // selli->next->order.quantity << " �۸�:" << selli->next->order.price << std::endl;
                buyi->next->order.quantity -= selli->next->order.quantity;
				db.updateOrder(buyi->next->order.Order_id, buyi->next->order.userid, buyi->next->order.price, buyi->next->order.quantity, QString::fromStdString(buyi->next->order.symbol), buyi->next->order.side);
				//Account*buyer = Ac.find_user(buyi->next->order.userid);//�ҵ����id��ָ����û�
				Account buyer(buyi->next->order.userid);
				buyer.upgrade(buyi->next->order.symbol, selli->next->order.quantity, (selli->next->order.quantity*selli->next->order.price), buyi->next->order);
				Account seller(selli->next->order.userid);
				//Account*seller = Ac.find_user(selli->next->order.userid);//�ҵ�����id��ָ����û�
				seller.upgrade(selli->next->order.symbol, selli->next->order.quantity, (selli->next->order.quantity*selli->next->order.price), selli->next->order);
                selli->next->order.quantity = 0;//clear the quantity
				db.removeOrder(selli->next->order.Order_id);//
            }
            market_price = selli->next->order.price; //���¹ɼۣ�
        }
        else {
            buyi = buyi->next;
        }
        price_list.push_back(market_price);//����б�洢��ÿ�εĹɼۣ�������������ͼ�Σ�
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