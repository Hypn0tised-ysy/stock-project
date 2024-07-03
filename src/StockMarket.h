#pragma once
#include "ui_StockMarket.h"
#include <QMainWindow>

class StockMarket : public QMainWindow {
    Q_OBJECT
    
public:
    StockMarket(QWidget* parent = nullptr);
    ~StockMarket();

private:
    Ui_StockMarket* ui;
};