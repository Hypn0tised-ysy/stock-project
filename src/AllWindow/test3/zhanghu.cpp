#include "zhanghu.h"
#include "ui_zhanghu.h"

zhanghu::zhanghu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::zhanghu)
{
    ui->setupUi(this);
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


void zhanghu::on_pushButton_clicked()
{
    d0.show();
}

