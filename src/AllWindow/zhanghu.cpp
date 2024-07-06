#include "zhanghu.h"
#include "ui_zhanghu.h"

zhanghu::zhanghu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::zhanghu)
{
    ui->setupUi(this);
    connect(&j0,&jiaoyi::send_it,&d0,&dingdan::get_it);
    connect(&j1,&jiaoyi2::send_it,&d0,&dingdan::get_it);
}

zhanghu::~zhanghu()
{
    delete ui;
}

void zhanghu::on_tuichu_clicked()
{
    close();
}

void zhanghu::on_buy_clicked()
{
    j0.show();
}

void zhanghu::on_sold_clicked()
{
    j1.show();
}

void zhanghu::on_dindgan_clicked()
{
    d0.showit();
    d0.show();
}

void zhanghu::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    t0.show();
}

void zhanghu::on_balance_clicked()
{
    b0.show();
}
