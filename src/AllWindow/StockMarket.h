#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include "LoginWindow.h"
#include "MainMenu.h"
class StockMarket : public QMainWindow
{
    Q_OBJECT
    QStackedWidget *MainWindowStack;

public:
    StockMarket(QWidget *parent = nullptr);
    ~StockMarket();

private:
};