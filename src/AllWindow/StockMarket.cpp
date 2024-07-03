#include "StockMarket.h"

StockMarket::StockMarket(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindowStack = new QStackedWidget(this);
    setCentralWidget(MainWindowStack);
    setWindowTitle("Stock Market");
    resize(1920, 1080);
    show();
}

StockMarket::~StockMarket()
{
}