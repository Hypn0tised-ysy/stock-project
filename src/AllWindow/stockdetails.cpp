#include"ui_stockdetails.h"
#include"stockdetails.h"
#include"QTextStream"
#include"QString"
stockdetails::stockdetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stockdetails)
{
    ui->setupUi(this);
    setFixedSize(800, 500);
    resizeit();
}

stockdetails::~stockdetails()
{
    delete ui;
}


void stockdetails::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.6,heights*0.85,widths*0.2,heights*0.1);
    ui->tableWidget->setGeometry(widths*0.4,heights*0.25,widths*0.55,heights*0.6);
    ui->label_2->setGeometry(widths*0.4,heights*0.05,widths*0.1,heights*0.1);
    ui->ID->setGeometry(widths*0.5,heights*0.05,widths*0.15,heights*0.1);
    ui->label_4->setGeometry(widths*0.4,heights*0.15,widths*0.1,heights*0.1);
    ui->number->setGeometry(widths*0.5,heights*0.15,widths*0.15,heights*0.1);
    ui->label_6->setGeometry(widths*0.65,heights*0.15,widths*0.1,heights*0.1);
    ui->price->setGeometry(widths*0.75,heights*0.15,widths*0.15,heights*0.1);
    ui->label->setGeometry(widths*0,heights*0.1,widths*0.4,heights*0.7);
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
