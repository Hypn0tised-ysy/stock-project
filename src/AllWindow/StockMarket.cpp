#include "StockMarket.h"
#include <QVBoxLayout>

StockMarket::StockMarket(QWidget *parent)
    : QMainWindow(parent)
{
    MainWindowStack = new QStackedWidget(this);
    setCentralWidget(MainWindowStack);
    setWindowTitle("Stock Market");
    setFixedSize(1500, 800);
    auto NowWindow = new LoginWindow(this);
    MainWindowStack->addWidget(NowWindow);
    MainWindowStack->setCurrentWidget(NowWindow);
    show();
    connect(NowWindow, &LoginWindow::Userid, this, [this](int id)
            { nowuser = id; });
    connect(NowWindow, &LoginWindow::Changepage, this, [this]()
            {
        Account *NowUser = new Account(nowuser);
        auto MainMenuPage = new MainMenu(NowUser);
        MainWindowStack->addWidget(MainMenuPage);
        MainWindowStack->setCurrentIndex(1);
        connect(MainMenuPage, &MainMenu::tuichudenglu, this, [this]()
                { MainWindowStack->setCurrentIndex(0);
                nowuser = -1;
                delete MainWindowStack->widget(1); }); });
}
StockMarket::~StockMarket()
{
}
