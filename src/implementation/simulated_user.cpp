#include "simulated_user.h"
Simulated_user::Simulated_user(std::string _id,double _money){
    id = _id;
    money = _money;
}

void Simulated_user::create_s_acc() {
    for (int i = 0; i < 1000; i++) {
        std::string id = "s_user" + std::to_string(i); // �����û�id
        std::string password = "111111111";
        enroll(id, password);
    }
}
void Simulated_user::simulated_trade() {
    // �����ʱ������Ϊ60��
    const std::chrono::seconds timerInterval(60);

    // ������ʱ��
    while (true) {
        // ��ȡ��ǰʱ���
        auto startTime = std::chrono::steady_clock::now();

        std::string peo_id = "s_user" + std::to_string(rand() % 1000);
        srand((unsigned int)time(NULL));
        // ģ��10���û����н���
        for (int i = 0; i < 10; i++) {
            // ������ɽ��׶�������
            int d = 0;
            for (int j = 0; j < 7; j++)
            {
                d = d * 10 + rand() % 9 + 1;
            }
            int order_id = d;
            std::string peo_id = "s_user" + std::to_string(rand()%1000);
            int j = rand() % 9;
            double price = stock.stk[j].market_price;
            int quantity = rand() % 100 + 1; // �����������
            bool side = rand() % 2; // 0Ϊ���룬1Ϊ����

            Order order(order_id, peo_id, price, quantity,stk[j].symbol, side);

            

            // ��Ӷ�������Ʊ����ϵͳ��
            stock.add_order(order);

            
        }

        // ������һ��ʱ���
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

        // �ȴ�ֱ���ﵽָ����ʱ����
        if (elapsedTime < timerInterval) {
            std::this_thread::sleep_for(timerInterval - elapsedTime);
        }
    }
}


void Simulated_user::upgrade(std::string _sym, int _sum, double price, Order& order)//���¿����Ϣ,����ָ���ļ۸�
{
    if (!order.side)//�����������Ϣ
    {
        this->money -= price;  
        if (this->stocks.empty())//����ֿ�Ϊ��
        {
            stocks* my_new = new My_stock(_sym, _sum);
            this->stocks.push_back(my_new);//���µĹ�Ʊ��Ϣ�洢��������
        }
        else//����ֿⲻΪ��
        {
            bool is_find = false;//�Ƿ��ҵ��и��ֹ�Ʊ
            for (auto tem : stocks)
            {
                if (tem->get_name() == _sym)//���������������Ʊ���ͽ�������
                {
                    tem->setnew_sum(tem->get_sum() + _sum);//�����µ�����
                    is_find = true;
                    break;
                }
            }
            //��������û�����ֹ�Ʊ���Ǿ���ӽ�ȥ
            if (!is_find)
            {
                My_stock* my_new = new My_stock(_sym, _sum);
                this->stocks.push_back(my_new);//���µĹ�Ʊ��Ϣ�洢��������
            }

        }

    }
    else//�����������Ϣ,//֮ǰ�Ѿ��ж����ֿ�Ҫ�ж�Ӧ����������������������Ӧ��Ĭ�ϲֿ����ж�Ӧ�Ķ�����
    {
        for (auto tem : stocks)
        {
            if (_sym == tem->get_name())//�ҵ��˲ֿ�Ŀ����
            {
                tem->setnew_sum(tem->get_sum() - _sum);//���¿�������
                this->money += price;//׬Ǯ��
                break;
            }
        }
    }
}


Order add_my_order(int order_id, Simulated_user* user, double price, int sum, std::string sym, bool side)
{

    std::vector<My_stock*> my = user->show_my_stock(); 
    if (!side)											// ���붩��
    {
        if (user->is_oktobuy(price * sum, user)) // �Ƿ����㹻�Ľ��ȥ�ύ���붩��
        {
            Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // �������붩��

            return mynew;
        }
        else
        {
            
            Order error = Order(); 
            return error;
        }

    }
    else // ��������--ƥ���Լ��Ŀ���Ƿ��ж�Ӧ���ŵĹ�Ʊ�Ͷ�Ӧ�������Ĺ�Ʊ
    {
        // ����ֿ�Ϊ��
        if (my.empty()) 
        {
            
            Order error = Order(); // �������붩��
            return error;
        }
        for (auto tem : my) 
        {
            if (tem->get_name() == sym) // �����Լ��Ŀ�����ҵ��˶�Ӧ�Ĺ�Ʊ����
            {
                if (sum <= tem->get_sum()) // �����Լ���������㹻���ύ��������
                {
                    Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // ��������
                    return mynew;
                }
                else // ����й���������������ô�ඩ��
                {
                    
                    Order error = Order(); // �ն�������ʱ����ô�жϴ���
                    return error;
                }
            }
        }
      
        Order error = Order(); // �ն�������ʱ����ô�жϴ���
        return error;
    }
}


