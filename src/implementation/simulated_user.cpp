#include "simulated_user.h"
#include "../database/database.h"
extern Database db;


void Simulated_user::create_s_acc() {
    for (int i = 0; i < 1000; i++) {
        std::string name = "s_user" + std::to_string(i+1); // �����û�id
        std::string password = "111111111";
        enroll(name, password);
    }
}
void Simulated_user::simulated_trade() {
    // �����ʱ������Ϊtick
    const std::chrono::seconds timerInterval(tick);

    // ������ʱ��
    while (true) {
        // ��ȡ��ǰʱ���
        auto startTime = std::chrono::steady_clock::now();
        //�������������
        srand(time(NULL));
        //����¼�����
        std::string ev = "Event";
        //�ɼ��ǵ�
        bool gob = rand() % 2;
        //�����¼�e
        Event e(ev, gob);
        //��ȡ��Ʊ����
        int n = db.getStocksList.size();
        //��Ʊ���
        int s_id = rand() % n+1;
        //��ȡ��Ʊ����
        Stock s=db.getStock(s_id);

        Event.impact(s);
       
        // ģ��10���û����н���
        for (int i = 0; i < 10; i++) {
            // ������ɽ��׶�������
           
            int peo_id = rand() % 1000+1;
            double price;
            int quantity;
            double ra = (rand() % 5 + 1) / 100;
                //�������û������1��300��
                if (1 <= peo_id <= 300) {
                    //���ݵ�ǰ���ƾ����߼��������ǹ�Ʊ���ǵ������µ���Ʊ
                    //����¼����ܵ���s��Ʊ����
                    if (gob) {
                        //�߼����������Ʊ
                        price = s.market_price * (1 + ra);
                        quantity = 20* (rand() % 9 + 1);
                        add_my_order(peo_id, price, quantity, s.symbol, !gob);
                    }
                    //����¼�������s��Ʊ
                    else {
                        //���ֿ�����s��Ʊ������У��ͼ�����
                        for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                        {
                            if (s.symbol == db.getMyStock(peo_id)[i].symbol)
                            {
                                price = s.market_price * (1 - ra);
                                //����һ��s��Ʊ
                                quantity = db.getMyStock(peo_id)[i].sum /2;
                                add_my_order(peo_id, price, quantity, s.symbol, !gob);
                                break;
                            }
                        }
                    }
                }
            //�������û������301��700��
                else if (300 < peo_id <= 700)
                {
                    bool ra2 = rand() % 2;
                    //�߼�����s��Ʊ
                    if (ra2)
                    {

                        price = s.market_price*1.01;
                        quantity = 10 * (rand() % 9 + 1);
                        add_my_order(peo_id, price, quantity, s.symbol, !ra2);
                    }
                    else
                    {//����ֿ���ڹ�Ʊ���ͼ��۳�
                        for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                        {
                            if (s.symbol == db.getMyStock(peo_id)[i].symbol)
                            {
                                price = s.market_price * 0.98;
                                quantity = db.getMyStock(peo_id)[i].sum / 2;
                                add_my_order(peo_id, price, quantity, s.symbol, ra2);
                                break;
                            }
                        }
                    }

                }
            //��С���û������701��1000��
                else if(700<peo_id<=1000)
                {
                    //����¼�������s��Ʊ����������
                    if (gob)
                    {
                        price = s.market_price * (1 + ra);
                        quantity = 10 * (rand() % 9 + 1);
                        add_my_order(peo_id, price, quantity, s.symbol, !gob);

                    }
                    else
                    {
                        //���ֿ�����s��Ʊ������У��ͼ�����
                        for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                        {
                            if (s.symbol == db.getMyStock(peo_id)[i].symbol)
                            {
                                price = s.market_price * (1 - ra);
                                //����ȫ����Ʊ
                                quantity = db.getMyStock(peo_id)[i].sum ;
                                add_my_order(peo_id, price, quantity, s.symbol, !gob);
                                break;
                            }
                        }
                    }
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





