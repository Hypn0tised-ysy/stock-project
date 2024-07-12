#include"ui_account.h"
#include "ui_ui_account.h"
#include "../database/database.h"
#include"Mainmenu.h"
extern Account* real_NowUser;
extern Database db;
zhanghu::zhanghu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::zhanghu)
{ 
    ui->setupUi(this);
    setFixedSize(1500, 800);
    init();
    resizeit();
    showit();
}

zhanghu::~zhanghu()
{
    delete ui;
}

void zhanghu::init(){
    ui->nicheng->setText(QString::fromStdString(real_NowUser->return_username()));
    ui->ID->setText(QString::fromStdString(std::to_string(real_NowUser->return_id())));

    ui->balance_text->setText(QString::number(real_NowUser->return_money(),'f',2));
    ms=real_NowUser->show_my_stock();
}
void zhanghu::showit()
{
    ui->tableWidget->setRowCount(ms.size());
    ms=real_NowUser->show_my_stock();
    for(int i=0;i<ms.size();i++){
        ui->tableWidget->setRowHeight(i,10);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
        QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(ms[i].get_name()));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,0,item);
        item=new QTableWidgetItem(QString::fromStdString(this->mp1[ms[i].get_name()].name));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,1,item);
        item=new QTableWidgetItem(QString::fromStdString(std::to_string(ms[i].get_sum())));
        ui->tableWidget->setItem(i,2,item);
        item->setFlags(Qt::ItemIsEnabled);
    }
    ui->balance_text->setText(QString::number(real_NowUser->return_money(),'f',2));
}
void zhanghu::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->tuichu->setGeometry(widths*0.8,heights*0.85,widths*0.15,heights*0.1);
    ui->dindgan->setGeometry(widths*0.57,heights*0.85,widths*0.15,heights*0.1);
    ui->sold->setGeometry(widths*0.4,heights*0.85,widths*0.15,heights*0.1);
    ui->buy->setGeometry(widths*0.23,heights*0.85,widths*0.15,heights*0.1);
    ui->name->setGeometry(widths*0.03,heights*0.3,widths*0.2,heights*0.1);
    ui->nicheng->setGeometry(widths*0.03,heights*0.4,widths*0.2,heights*0.1);
    ui->ID_text->setGeometry(widths*0.03,heights*0.5,widths*0.2,heights*0.1);
    ui->ID->setGeometry(widths*0.03,heights*0.6,widths*0.2,heights*0.1);
    ui->listWidget->setGeometry(widths*0.8,heights*0.5,widths*0.15,heights*0.3);
    ui->balance->setGeometry(widths*0.8,heights*0.35,widths*0.15,heights*0.1);
    ui->balance_text->setGeometry(widths*0.8,heights*0.1,widths*0.15,heights*0.2);
    ui->tableWidget->setGeometry(widths*0.3,heights*0.1,widths*0.35,heights*0.7);
    ui->tableWidget->setColumnWidth(0,widths*0.113);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(1,widths*0.113);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(2,widths*0.113);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->label->setGeometry(widths*0.03,heights*0.05,widths*0.15,heights*0.2);
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
    d0.show();
    d0.showit();
}

void zhanghu::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    t0.show();
}

void zhanghu::on_balance_clicked()
{
    b0.show();
}
