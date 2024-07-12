#ifndef STOCKMAP_H
#define STOCKMAP_H

#include<map>
#include<string>
#include"stock.h"
#include<vector>
std::map<std::string, Stock> BuildStockMap(std::vector<Stock> &stocklist);

#endif // STOCKMAP_H
