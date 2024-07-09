#include "simulated_user.h"
Simulated_user::Simulated_user(std::string _id,double _money){
    id = _id;
    money = _money;
}

void Simulated_user::create_s_acc() {
    for (int i = 0; i < 1000; i++) {
        std::string id = "s_user" + std::to_string(i); // 生成用户id
        std::string password = "111111111";
        enroll(id, password);
    }
}
void Simulated_user::simulated_trade() {
    // 定义计时器周期为60秒
    const std::chrono::seconds timerInterval(60);

    // 启动计时器
    while (true) {
        // 获取当前时间点
        auto startTime = std::chrono::steady_clock::now();

        std::string peo_id = "s_user" + std::to_string(rand() % 1000);
        srand((unsigned int)time(NULL));
        // 模拟10个用户进行交易
        for (int i = 0; i < 10; i++) {
            // 随机生成交易订单数据
            int d = 0;
            for (int j = 0; j < 7; j++)
            {
                d = d * 10 + rand() % 9 + 1;
            }
            int order_id = d;
            std::string peo_id = "s_user" + std::to_string(rand()%1000);
            int j = rand() % 9;
            double price = stock.stk[j].market_price;
            int quantity = rand() % 100 + 1; // 随机生成数量
            bool side = rand() % 2; // 0为买入，1为卖出

            Order order(order_id, peo_id, price, quantity,stk[j].symbol, side);

            

            // 添加订单到股票交易系统中
            stock.add_order(order);

            
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


void Simulated_user::upgrade(std::string _sym, int _sum, double price, Order& order)//更新库存信息,根据指定的价格
{
    if (!order.side)//如果是买入信息
    {
        this->money -= price;  
        if (this->stocks.empty())//如果仓库为空
        {
            stocks* my_new = new My_stock(_sym, _sum);
            this->stocks.push_back(my_new);//将新的股票信息存储进入库存中
        }
        else//如果仓库不为空
        {
            bool is_find = false;//是否找到有该种股票
            for (auto tem : stocks)
            {
                if (tem->get_name() == _sym)//如果库存中有这个股票，就进行增加
                {
                    tem->setnew_sum(tem->get_sum() + _sum);//设置新的数量
                    is_find = true;
                    break;
                }
            }
            //如果库存中没有这种股票，那就添加进去
            if (!is_find)
            {
                My_stock* my_new = new My_stock(_sym, _sum);
                this->stocks.push_back(my_new);//将新的股票信息存储进入库存中
            }

        }

    }
    else//如果是卖出信息,//之前已经判定过仓库要有对应东西才能卖出，所以这里应该默认仓库是有对应的东西的
    {
        for (auto tem : stocks)
        {
            if (_sym == tem->get_name())//找到了仓库的库存了
            {
                tem->setnew_sum(tem->get_sum() - _sum);//更新库存的数量
                this->money += price;//赚钱了
                break;
            }
        }
    }
}


Order add_my_order(int order_id, Simulated_user* user, double price, int sum, std::string sym, bool side)
{

    std::vector<My_stock*> my = user->show_my_stock(); 
    if (!side)											// 买入订单
    {
        if (user->is_oktobuy(price * sum, user)) // 是否有足够的金额去提交买入订单
        {
            Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // 创建买入订单

            return mynew;
        }
        else
        {
            
            Order error = Order(); 
            return error;
        }

    }
    else // 卖出订单--匹配自己的库存是否有对应代号的股票和对应的数量的股票
    {
        // 如果仓库为空
        if (my.empty()) 
        {
            
            Order error = Order(); // 创建买入订单
            return error;
        }
        for (auto tem : my) 
        {
            if (tem->get_name() == sym) // 当在自己的库存中找到了对应的股票代码
            {
                if (sum <= tem->get_sum()) // 并且自己库存量还足够，提交卖出订单
                {
                    Order mynew = Order(order_id, user->get_id(user), price, sum, sym, side); // 创建订单
                    return mynew;
                }
                else // 库存中股数不足以卖出这么多订单
                {
                    
                    Order error = Order(); // 空订单，到时候看怎么判断错误
                    return error;
                }
            }
        }
      
        Order error = Order(); // 空订单，到时候看怎么判断错误
        return error;
    }
}


