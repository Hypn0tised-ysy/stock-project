#include "simulated_user.h"
#include "../database/database.h"
#include <QVariantList>
extern Database db;

Simulated_user::Simulated_user(int _id):Account (_id){};


void Simulated_user::s_trade(double _price,int _quantity,QString &_symbol,bool _side){
    add_my_order(id,_price,_quantity,_symbol,_side);
}


void create_s_acc() {
    for (int i = 0; i < 1000; i++) {
        std::string name = "s_user" + std::to_string(i+1); // ????id
        std::string password = "111111111";

        enroll(name, password);
    }
}


void simulated_trade() {

        //???????
        srand(time(NULL));
        //??????
        std::string ev = "Event";
        //????
        bool gob = rand() % 2;
        //????e
        Event e(ev, gob);
        //??????
        int n = db.getStocksList().size();
        //????
        int s_id = rand() % n + 1;
        //??????
        Stock s = db.getStocksList()[s_id - 1];

        e.impact(s);
        QString sym = QString::fromStdString(s.symbol);
        // ??10???????
        for (int i = 0; i < 10; i++) {
            // ??????????

            int ra1 = rand() % db.getBotslist().size() + 1;
            int peo_id = db.getBotslist()[ra1];
            double price;
            int quantity;
            double ra = (rand() % 5 + 1) / 100;
            Simulated_user robot(peo_id);
            //????????1?300?
            if (ra1<300) {
                //?????????????????????????
                //????????s????
                if (gob) {
                    //????????
                    price = s.market_price * (1 + ra);
                    quantity = 20 * (rand() % 9 + 1);
                    robot.s_trade(price, quantity, sym, !gob);

                }
                //???????s??
                else {
                    //??????s???????????
                    for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                    {
                        if (s.symbol == db.getMyStock(peo_id)[i].get_name())
                        {
                            price = s.market_price * (1 - ra);
                            //????s??
                            quantity = db.getMyStock(peo_id)[i].get_sum() / 2;
                            robot.s_trade(price, quantity, sym, !gob);
                            break;
                        }
                    }
                }
            }
            //????????301?700?
            else if (300 <= ra1 && ra1 < 700)
            {
                bool ra2 = rand() % 2;
                //????s??
                if (ra2)
                {

                    price = s.market_price * 1.01;
                    quantity = 10 * (rand() % 9 + 1);
                    robot.s_trade(price, quantity, sym, !gob);
                }
                else
                {//?????????????
                    for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                    {
                        if (s.symbol == db.getMyStock(peo_id)[i].get_name())
                        {
                            price = s.market_price * 0.98;
                            quantity = db.getMyStock(peo_id)[i].get_sum() / 2;
                            robot.s_trade(price, quantity, sym, !gob);
                            break;
                        }
                    }
                }

            }
            //????????701?1000?
            else if (700 <= ra1&&ra1 < 1000)
            {
                //???????s???????
                if (gob)
                {
                    price = s.market_price * (1 + ra);
                    quantity = 10 * (rand() % 9 + 1);
                    robot.s_trade(price, quantity, sym, !gob);

                }
                else
                {
                    //??????s???????????
                    for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                    {
                        if (s.symbol == db.getMyStock(peo_id)[i].get_name())
                        {
                            price = s.market_price * (1 - ra);
                            //??????
                            quantity = db.getMyStock(peo_id)[i].get_sum();
                            robot.s_trade(price, quantity, sym, !gob);
                            break;
                        }
                    }
                }
            }
        }


}

