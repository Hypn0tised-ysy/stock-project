#ifndef ZHANGHU_H
#define ZHANGHU_H

#include <QWidget>
#include <QDialog>
#include"jiaoyi.h"
#include"ui_jiaoyi.h"
#include"jiaoyi2.h"
#include"ui_jiaoyi2.h"
#include"dingdan.h"
#include"ui_dingdan.h"
#include"balance.h"
#include"ui_balance.h"
#include"trade_details.h"
#include"ui_trade_details.h"
#include<QListWidget>
namespace Ui {
class zhanghu;
}

class zhanghu : public QWidget
{
    Q_OBJECT

public:
    explicit zhanghu(QWidget *parent = nullptr);
    ~zhanghu();
    void resizeit();
private slots:
    void on_tuichu_clicked();

    void on_buy_clicked();

    void on_sold_clicked();

    void on_dindgan_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_balance_clicked();

private:
    Ui::zhanghu *ui;
     jiaoyi j0;
    jiaoyi2 j1;
     dingdan d0;
    balance b0;
     trade_details t0;
};

#endif // ZHANGHU_H
