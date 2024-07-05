#include "trade_details.h"
#include "ui_trade_details.h"

trade_details::trade_details(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::trade_details)
{
    ui->setupUi(this);
}

trade_details::~trade_details()
{
    delete ui;
}

void trade_details::on_pushButton_clicked()
{
    close();
}

