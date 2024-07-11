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
int main(int argc, char *argv[])
{
  
    QString path = QDir::currentPath();
    QApplication::addLibraryPath(path + QString("/plugins"));
    std::wstring pythonHome = path.toStdWString();
    QPluginLoader loader(path + QString("/plugins/sqldrivers/qsqlite.dll"));
    QApplication a(argc, argv);
    StockMarket w;
    w.show();
    PriceChart priceChart;
    //priceChart.show();
    return a.exec();
    // 以下为测试代码
}
