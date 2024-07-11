#include "ui_order.h"
#include "ui_ui_order.h"
#include<vector>
#include<QString>
#include<QMessageBox>
dingdan::dingdan(Account *_NowUser,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dingdan)
{   o_NowUser=_NowUser;
    ui->setupUi(this);
    setFixedSize(600, 500);
    resizeit();
}

dingdan::~dingdan()
{
    delete ui;
}

void dingdan::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.7,heights*0.85,widths*0.2,heights*0.1);
    ui->delete_2->setGeometry(widths*0.2,heights*0.85,widths*0.2,heights*0.1);
    ui->tableWidget->setGeometry(widths*0.1,heights*0.1,widths*0.8,heights*0.6);
    ui->tableWidget->setColumnWidth(0,widths*0.15);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(1,widths*0.15);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(2,widths*0.15);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(3,widths*0.15);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(4,widths*0.15);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);

}


void dingdan::on_close_clicked()
{
    close();
}

void dingdan::showit()
{   std::vector<Order> tmp=o_NowUser->show_my_order();
    ui->tableWidget->setRowCount(tmp.size());
    for(int i=0;i<tmp.size();i++){
        ui->tableWidget->setRowHeight(i,10);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
        QString s1,s2,s3,s4,s5;
        s1=QString::fromStdString(tmp[i].symbol);
        QTableWidgetItem *item=new QTableWidgetItem(s1);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,0,item);

        s2=QString::fromStdString(std::to_string(tmp[i].Order_id));
        item=new QTableWidgetItem(s2);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,1,item);

        s3=QString::fromStdString(std::to_string(tmp[i].price));
        item=new QTableWidgetItem(s3);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,2,item);

        bool bs=tmp[i].side;
        if(!bs)
            s4="买入";
        else s4="卖出";
        item=new QTableWidgetItem(s4);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,3,item);

        s5=QString::fromStdString(std::to_string(tmp[i].quantity));
        item=new QTableWidgetItem(s5);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,4,item);
    }
}
void dingdan::on_delete_2_clicked()
{
    if(delete_ID==-1)
    {
        QMessageBox::information(this,"警告","未选择相应订单",QMessageBox::Close);
        return;
    }
    else
    {
       int tmp= o_NowUser->removeOrder(delete_ID);
        if(tmp<=0)
       {
           QMessageBox::information(this,"警告","无法删除相应订单",QMessageBox::Close);
            return;
       }
        else
        {
            QMessageBox::information(this,"提示","已删除相应订单",QMessageBox::Close);
           showit();return;
        }
    }
}

void dingdan::on_tableWidget_cellDoubleClicked(int row, int column)
{   QString tmp=ui->tableWidget->item(row,1)->text();
    delete_ID=tmp.toInt();
}

