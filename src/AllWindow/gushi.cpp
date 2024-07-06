#include "gushi.h"
#include "ui_gushi.h"
#include<QString>
#include<string>
#include<vector>

gushi::gushi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gushi)
{
    ui->setupUi(this);
    timer=new QTimer;
    time_record=new QTime;
    ui->times->setDigitCount(8);
    init_time();
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(update_time()));
    connect(this,&gushi::send,&s0,&stockdetails::get);
    connect(this,&gushi::send1,&s0,&stockdetails::get1);
    connect(this,&gushi::send2,&s0,&stockdetails::get2);
    connect(this,&gushi::send3,&s0,&stockdetails::get3);

}

gushi::~gushi()
{
    delete ui;
}

void gushi::init_time(){
    time_record->setHMS(0,1,0);
    ui->times->display(time_record->toString("hh:mm:ss"));
}

void gushi::update_time(){
    *time_record = time_record->addSecs(-1);
    if(time_record->minute()==0&&time_record->second()==0){
        showit();
        init_time();
    }
    ui->times->display(time_record->toString("hh:mm:ss"));

}

void gushi::on_close_clicked()
{
    close();
}
std::vector<QString> v1={"1452145","14521452","6521554","5484785","52114562","58746144","5523651","52445214","1255412","14521452"};
std::vector<QString> v2={"A","B","C","D","E","F","G","H","I","J"};
std::vector<QString> v3={"5","6","412","52","41","51","10","14","1254","771"};
std::vector<QString> v4={"15201","52512","51525","51452","54152","511452","51521","478544","41425","145212"};
QString s1,s2,s3,s4;
void gushi::showit(){
    ui->tableWidget->setRowCount(10);
    for(int i=0;i<10;i++){
        s1=v1[i];
        QTableWidgetItem *item=new QTableWidgetItem(s1);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,ID,item);
        s2=v2[i];
        item=new QTableWidgetItem(s2);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,gongsi,item);
        s3=v3[i];
        item=new QTableWidgetItem(s3);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,gujia,item);
        s4=v4[i];
        item=new QTableWidgetItem(s4);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,gushu,item);
    }
}


void gushi::on_show_clicked()
{
    std::vector<QString> v5;
    v5=v1;
    v1=v2;
    v2=v5;
}


void gushi::on_tableWidget_cellDoubleClicked(int row, int column)
{   emit send1(v1[row]);
    emit send2(v3[row]);
    emit send3(v4[row]);
    s0.show();
    s0.showit();

}

