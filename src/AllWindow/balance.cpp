#include "balance.h"
#include "ui_balance.h"

balance::balance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::balance)
{
    ui->setupUi(this);
}

balance::~balance()
{
    delete ui;
}

void balance::on_close_clicked()
{
    close();
}

