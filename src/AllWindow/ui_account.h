#ifndef UI_ACCOUNT_H
#define UI_ACCOUNT_H

#include <QWidget>
#include <QDialog>
#include <vector>
#include"ui_buy_order.h"
#include"ui_buy_order.h"
#include"ui_sold_order.h"
#include"ui_sold_order.h"
#include"ui_order.h"
#include"ui_ui_order.h"
#include"balance.h"
#include"ui_balance.h"
#include"trade_details.h"
#include"ui_trade_details.h"
#include<QListWidget>
#include "../implementation/Account.h"
#include "../implementation/My_stock.h"
#include "../implementation/stock.h"
namespace Ui {
class zhanghu;
}

class zhanghu : public QWidget
{
    Q_OBJECT

public:
    zhanghu(Account *NowUser,QWidget *parent = nullptr);
    ~zhanghu();
    void resizeit();
    void showit();
    void init();
    std::vector<Stock> all_stocks;
private slots:
    void on_tuichu_clicked();

    void on_buy_clicked();

    void on_sold_clicked();

    void on_dindgan_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_balance_clicked();

private:
    Ui::zhanghu *ui;
    jiaoyi* j0;
    jiaoyi2* j1;
    dingdan* d0;
    balance b0;
    trade_details t0;
    Account *z_NowUser;
    std::vector<My_stock> ms;
};

#endif // UI_ACCOUNT_H
