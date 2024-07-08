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
    connect(NowWindow, &LoginWindow::Changepage, this, [this]()
            {

                auto MainMenuPage = new MainMenu(Account(),this);
                 MainWindowStack->addWidget(MainMenuPage);
                 MainWindowStack->setCurrentIndex(1);
                 delete MainWindowStack->widget(0); });
}

StockMarket::~StockMarket()
{
}