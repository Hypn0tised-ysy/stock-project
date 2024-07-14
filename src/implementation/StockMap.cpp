#include"StockMap.h"




std::map<std::string, Stock> BuildStockMap(std::vector<Stock> &stocklist)
{
    std::map<std::string, Stock> stockmap;
    for (auto tem : stocklist)
    {
        stockmap[tem.symbol] = tem;
    }
    return stockmap;
}
