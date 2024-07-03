#pragma once
#include <QMainWindow>
#include <QStackedWidget>

class StockMarket : public QMainWindow
{
    Q_OBJECT
    QStackedWidget *MainWindowStack;

public:
    StockMarket(QWidget *parent = nullptr);
    ~StockMarket();

private:
};