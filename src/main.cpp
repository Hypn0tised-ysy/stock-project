#include <python.h>
#include "AllWindow/StockMarket.h"
#include <QApplication>
#pragma comment(lib, "user32.lib")
#include <QPluginLoader>
#include <QDir>
int main(int argc, char *argv[])
{
    QString path = QDir::currentPath();
    QApplication::addLibraryPath(path + QString("/plugins"));
    QPluginLoader loader(path + QString("/plugins/sqldrivers/qsqlite.dll"));
    QApplication a(argc, argv);
    StockMarket w;
    w.show();
    return a.exec();
    // 以下为测试代码
}
