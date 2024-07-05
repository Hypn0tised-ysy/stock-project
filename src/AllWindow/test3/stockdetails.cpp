#include "stockdetails.h"
#include "ui_stockdetails.h"
#include"QTextStream"
#include"QString"
StockDetails::StockDetails(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StockDetails)
{
    ui->setupUi(this);
}

StockDetails::~StockDetails()
{
    delete ui;
}
int row;QString s_ID,s_price,s_number;
void StockDetails::get(int i){
    row=i;
}
void StockDetails::get1(QString ID){
    s_ID=ID;
}
void StockDetails::get2(QString price){
    s_price=price;
}
void StockDetails::get3(QString number){
    s_number=number;
}
void StockDetails::showit(){
    ui->ID->setText(s_ID);
    ui->number->setText(s_number);
    ui->price->setText(s_price);
}
void StockDetails::on_close_clicked()
{
    close();
}

