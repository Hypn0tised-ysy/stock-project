#include "ui_stockmarket.h"
#include "ui_ui_stockmarket.h"
#include<QString>
#include<string>
#include<vector>

gushi::gushi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gushi)
{
    ui->setupUi(this);
    setFixedSize(1500, 800);
    timer=new QTimer;
    time_record=new QTime;
    ui->times->setDigitCount(8);
    init_time();
    timer->start(1000);//1000为正常时间，目前暂时加速。
    connect(timer,SIGNAL(timeout()),this,SLOT(update_time()));
    resizeit();

}

gushi::~gushi()
{
    delete ui;
}

void gushi::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.7,heights*0.8,widths*0.15,heights*0.1);
    ui->tableWidget->setGeometry(widths*0.1,heights*0.2,widths*0.8,heights*0.5);
    ui->tableWidget->setColumnWidth(0,widths*0.26);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(1,widths*0.26);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(2,widths*0.26);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->times->setGeometry(widths*0.7,heights*0.05,widths*0.2,heights*0.1);
}


void gushi::init_time(){
    time_record->setHMS(8,0,0);
    ui->times->display(time_record->toString("hh:mm:ss"));
}

void gushi::update_time(){
    *time_record = time_record->addSecs(1);
    if(time_record->second()==0&&time_record->minute()==0){
        showit();//一小时一更新股市
    }
    ui->times->display(time_record->toString("hh:mm:ss"));

}

void gushi::on_close_clicked()
{
    close();
}


void gushi::showit(){
    ui->tableWidget->setRowCount(all_stocks.size());
    for(int i=0;i<all_stocks.size();i++){
        ui->tableWidget->setRowHeight(i,10);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
        Stock tmp=all_stocks[i];
        QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(tmp.symbol));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,0,item);

        item=new QTableWidgetItem(QString::fromStdString(tmp.name));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,1,item);

        item=new QTableWidgetItem(QString::number(tmp.market_price,'f',2));
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,2,item);

    }
    //根据数据库中的股票数据来自动显示股票信息。
}




void gushi::on_tableWidget_cellDoubleClicked(int row, int column)
{
    stockdetails *s=new stockdetails;
    connect(this,&gushi::send,s,&stockdetails::get);
    connect(this,&gushi::send1,s,&stockdetails::get1);
    connect(this,&gushi::send2,s,&stockdetails::get2);
    connect(this,&gushi::send3,s,&stockdetails::get3);
    Stock tmp=all_stocks[row];
    emit send1(QString::fromStdString(tmp.symbol));
    emit send3(QString::fromStdString(tmp.name));
    emit send2(QString::number(tmp.market_price,'f',2));
    s->show();
    s->showit();
//可同时开启多个窗口，同时查看不同股票详情。
}

