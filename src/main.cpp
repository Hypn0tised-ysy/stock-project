#pragma push_macro("slots")
#undef slots
#include <Python.h>
#pragma pop_macro("slots")
#include "AllWindow/StockMarket.h"
#include <QApplication>
#pragma comment(lib, "user32.lib")
#include <QPluginLoader>
#include <QDir>
#include <string>
#include "./database/database.h"
#include "./AllWindow/PriceChart.h"
#include "./AllWindow/RTimePriceChart.h"
int main(int argc, char *argv[])
{
  
    QString path = QDir::currentPath();
    QApplication::addLibraryPath(path + QString("/plugins"));
    std::wstring pythonHome = path.toStdWString();
    QPluginLoader loader(path + QString("/plugins/sqldrivers/qsqlite.dll"));
    QApplication a(argc, argv);
    StockMarket w;
    w.show();
    
    QChartView *pchart;
    //创建一个空windows
    pchart=BuildPriceChart("100001");
    std::vector<StockPrice> test;
    test=db.getStockPrice("100001");
    test.resize(20);
    RTimePriceChartView *pRTimePriceChartView = new RTimePriceChartView(test);
    QMainWindow window;
    window.setCentralWidget(pRTimePriceChartView->RTimechart);
    window.resize(800, 600);
    window.show();
    //priceChart.show();
    pRTimePriceChartView->UpdateNewSecond(52);
    pRTimePriceChartView->UpdateNewSecond(54);
    pRTimePriceChartView->UpdateNewSecond(60);
    for(int i=1;i<20;i++)
    {
        pRTimePriceChartView->UpdateNewSecond(50);
    }
    return a.exec();
    // 以下为测试代码
}
/*使用案例
pchart=BuildPriceChart("100001");//k值图
window.setCentralWidget(pchart);//这里用任何的添加widget方法都可以
std::vector<StockPrice> test;
test=db.getStockPrice("100001");
test.resize(20);//这里应该替换成一天的长度，取最近一天的数据 一天600tick，如果最后一个tick是700，那么就取600~700
RTimePriceChartView *pRTimePriceChartView = new RTimePriceChartView(test);
window.setCentralWidget(pRTimePriceChartView->RTimechart);//这里用任何的添加widget方法都可以
pRTimePriceChartView->UpdateNewSecond(52);//更新最新股价

*/
