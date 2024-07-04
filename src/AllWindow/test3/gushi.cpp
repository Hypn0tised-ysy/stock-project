#include "gushi.h"
#include "ui_gushi.h"
#include<QString>
#include<vector>
gushi::gushi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gushi)
{
    ui->setupUi(this);
}

gushi::~gushi()
{
    delete ui;
}

void gushi::on_close_clicked()
{   ui->tableWidget->clear();
    close();
}


QString s1="125412";
QString s2="miHoYo";
void gushi::on_show_clicked()
{
    ui->tableWidget->setRowCount(10);
    for(int i=0;i<10;i++){
        QTableWidgetItem *item=new QTableWidgetItem(s1);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,ID,item);
        item=new QTableWidgetItem(s2);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,gongsi,item);
    }

}

