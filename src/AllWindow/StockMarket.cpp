#include "StockMarket.h"
#include <QVBoxLayout>

StockMarket::StockMarket(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindowStack = new QStackedWidget(this);
    setCentralWidget(MainWindowStack);
    setWindowTitle("Stock Market");
    setFixedSize(1920, 1080);
    auto NowWindow = new LoginWindow(this);
    MainWindowStack->addWidget(NowWindow);
    MainWindowStack->setCurrentWidget(NowWindow);
    show();
}

StockMarket::~StockMarket()
{
}