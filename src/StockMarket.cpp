#include "StockMarket.h"

StockMarket::StockMarket(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui_StockMarket)
{
    ui->setupUi(this);
}

StockMarket::~StockMarket()
{
    delete ui; 
}