#include"ui_stockdetails.h"
#include"stockdetails.h"
#include"QTextStream"
#include"QString"
stockdetails::stockdetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stockdetails)
{
    ui->setupUi(this);
}

stockdetails::~stockdetails()
{
    delete ui;
}
int row;QString s_ID,s_price,s_number;
void stockdetails::get(int i){
    row=i;
}
void stockdetails::get1(QString ID){
    s_ID=ID;
}
void stockdetails::get2(QString price){
    s_price=price;
}
void stockdetails::get3(QString number){
    s_number=number;
}
void stockdetails::showit(){
    ui->ID->setText(s_ID);
    ui->number->setText(s_number);
    ui->price->setText(s_price);
}
void stockdetails::on_close_clicked()
{
    close();
}
