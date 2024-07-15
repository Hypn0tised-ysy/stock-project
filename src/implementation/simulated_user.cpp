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
        std::string name = "s_user" + std::to_string(i+1); // 生成用户id
        std::string password = "111111111";

        enroll(name, password);
    }
}


void simulated_trade() {
    // 定义计时器周期为tick
    const std::chrono::seconds timerInterval(30);

    // 启动计时器
    while (true) {
        // 获取当前时间点
        auto startTime = std::chrono::steady_clock::now();
        //设置随机数种子
        srand(time(NULL));
        //随机事件名称
        std::string ev = "Event";
        //股价涨跌
        bool gob = rand() % 2;
        //发生事件e
        Event e(ev, gob);
        //获取股票总数
        int n = db.getStocksList().size();
        //股票编号
        int s_id = rand() % n+1;
        //获取股票类型
        Stock s=db.getStocksList()[s_id-1];

        e.impact(s);
       QString sym=QString::fromStdString(s.symbol);
        // 模拟10个用户进行交易
        for (int i = 0; i < 10; i++) {
            // 随机生成交易订单数据
           
            int peo_id = rand() % 1000+1;
            double price;
            int quantity;
            double ra = (rand() % 5 + 1) / 100;
            Simulated_user robot(peo_id);
                //胆大型用户（编号1到300）
                if (1 <= peo_id &&peo_id<= 300) {
                    //根据当前形势决定高价买入上涨股票或是低卖出下跌股票
                    //如果事件可能导致s股票上涨
                    if (gob) {
                        //高价买入大量股票
                        price = s.market_price * (1 + ra);
                        quantity = 20* (rand() % 9 + 1);
                        robot.s_trade(price,quantity, sym,!gob);

                    }
                    //如果事件不利于s股票
                    else {
                        //检查仓库有无s股票，如果有，低价卖出
                        for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                        {
                            if (s.symbol == db.getMyStock(peo_id)[i].get_name())
                            {
                                price = s.market_price * (1 - ra);
                                //卖出一半s股票
                                quantity = db.getMyStock(peo_id)[i].get_sum()/2;
                                robot.s_trade(price,quantity, sym,!gob);
                                break;
                            }
                        }
                    }
                }
            //无脑型用户（编号301到700）
                else if (300 < peo_id &&peo_id<= 700)
                {
                    bool ra2 = rand() % 2;
                    //高价买入s股票
                    if (ra2)
                    {

                        price = s.market_price*1.01;
                        quantity = 10 * (rand() % 9 + 1);
                        robot.s_trade(price,quantity, sym,!gob);
                    }
                    else
                    {//如果仓库存在股票，低价售出
                        for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                        {
                            if (s.symbol == db.getMyStock(peo_id)[i].get_name())
                            {
                                price = s.market_price * 0.98;
                                quantity = db.getMyStock(peo_id)[i].get_sum() / 2;
                              robot.s_trade(price,quantity, sym,!gob);
                                break;
                            }
                        }
                    }

                }
            //胆小型用户（编号701到1000）
                else if(700<peo_id<=1000)
                {
                    //如果事件有利于s股票，谨慎购入
                    if (gob)
                    {
                        price = s.market_price * (1 + ra);
                        quantity = 10 * (rand() % 9 + 1);
                        robot.s_trade(price,quantity, sym,!gob);

                    }
                    else
                    {
                        //检查仓库有无s股票，如果有，低价卖出
                        for (int i = 0; i < db.getMyStock(peo_id).size(); i++)
                        {
                            if (s.symbol == db.getMyStock(peo_id)[i].get_name())
                            {
                                price = s.market_price * (1 - ra);
                                //卖出全部股票
                                quantity = db.getMyStock(peo_id)[i].get_sum();
                                robot.s_trade(price,quantity, sym,!gob);
                                break;
                            }
                        }
                    }
                }

        // 计算下一个时间点
        auto endTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

        // 等待直到达到指定的时间间隔
        if (elapsedTime < timerInterval) {
            std::this_thread::sleep_for(timerInterval - elapsedTime);
        }
    }

}
