#include "zhanghu.h"
#include "ui_zhanghu.h"

zhanghu::zhanghu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::zhanghu)
{
    ui->setupUi(this);
    setFixedSize(1500, 800);
    connect(&j0,&jiaoyi::send_it,&d0,&dingdan::get_it);
    connect(&j1,&jiaoyi2::send_it,&d0,&dingdan::get_it);
    resizeit();

}

zhanghu::~zhanghu()
{
    delete ui;
}


void zhanghu::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->tuichu->setGeometry(widths*0.8,heights*0.85,widths*0.15,heights*0.1);
    ui->dindgan->setGeometry(widths*0.57,heights*0.85,widths*0.15,heights*0.1);
    ui->sold->setGeometry(widths*0.4,heights*0.85,widths*0.15,heights*0.1);
    ui->buy->setGeometry(widths*0.23,heights*0.85,widths*0.15,heights*0.1);
    ui->yonghuxinxishezhi->setGeometry(widths*0.05,heights*0.85,widths*0.15,heights*0.1);
    ui->jianjie->setGeometry(widths*0.03,heights*0.56,widths*0.2,heights*0.2);
    ui->nicheng->setGeometry(widths*0.03,heights*0.43,widths*0.2,heights*0.1);
    ui->ID->setGeometry(widths*0.03,heights*0.3,widths*0.2,heights*0.1);
    ui->listWidget->setGeometry(widths*0.8,heights*0.5,widths*0.15,heights*0.3);
    ui->balance->setGeometry(widths*0.8,heights*0.35,widths*0.15,heights*0.1);
    ui->balance_text->setGeometry(widths*0.8,heights*0.1,widths*0.15,heights*0.2);
    ui->tableWidget->setGeometry(widths*0.3,heights*0.1,widths*0.35,heights*0.7);
    ui->tableWidget->setColumnWidth(0,widths*0.158);
    ui->tableWidget->setColumnWidth(1,widths*0.158);
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
