#include"ui_stockdetails.h"
#include"stockdetails.h"
#include"QTextStream"
#include"QString"
#include "../database/database.h"
extern Database db;
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
    ui->tableWidget->setColumnWidth(0,widths*0.105);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(1,widths*0.105);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(2,widths*0.105);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(3,widths*0.105);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(4,widths*0.105);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);
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
    s_number=number;//应该为name，懒得改了。
}
void stockdetails::showit(){
    ui->ID->setText(s_ID);
    ui->number->setText(s_number);
    ui->price->setText(s_price);
    std::vector<Order> tmp1=db.getOrdersList(s_ID,true);
    std::vector<Order> tmp2=db.getOrdersList(s_ID,false);
    ui->tableWidget->setRowCount(tmp1.size()+tmp2.size());
    int i=0;
    for(;i<tmp1.size();i++)
    {
        ui->tableWidget->setRowHeight(i,10);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
        QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(tmp1[i].Peo_id));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,0,item);
        item=new QTableWidgetItem(QString::fromStdString(std::to_string(tmp1[i].Order_id)));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,1,item);
        item=new QTableWidgetItem("买入");
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,2,item);
        item=new QTableWidgetItem(QString::number(tmp1[i].price,'f',2));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,3,item);
        item=new QTableWidgetItem(QString::fromStdString(std::to_string(tmp1[i].quantity)));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,4,item);
    }
    for(int j=0;j<tmp2.size();j++)
    {
        ui->tableWidget->setRowHeight(i,10);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(j,QHeaderView::Fixed);
        QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(tmp2[j].Peo_id));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,0,item);
        item=new QTableWidgetItem(QString::fromStdString(std::to_string(tmp2[j].Order_id)));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,1,item);
        item=new QTableWidgetItem("卖出");
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,2,item);
        item=new QTableWidgetItem(QString::number(tmp2[j].price,'f',2));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,3,item);
        item=new QTableWidgetItem(QString::fromStdString(std::to_string(tmp2[j].quantity)));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,4,item);
    }
}
void stockdetails::on_close_clicked()
{
    close();
}
