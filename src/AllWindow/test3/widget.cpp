#include "widget.h"
#include "ui_widget.h"
#include"zhanghu.h"
#include"ui_zhanghu.h"
#include"gushi.h"
#include"ui_gushi.h"
#include"jiaoyi.h"
#include"ui_jiaoyi.h"
#include"hangqing.h"
#include"ui_hangqing.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    w_timer=new QTimer;
    w_time_record=new QTime;
    ui->w_time->setDigitCount(8);
    init_time();
    w_timer->start(100);
    connect(w_timer,SIGNAL(timeout()),this,SLOT(update_time()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::init_time(){
    w_time_record->setHMS(0,8,0);
    ui->w_time->display(w_time_record->toString("hh:mm:ss"));
}

void Widget::update_time(){
    *w_time_record = w_time_record->addSecs(1);
    if(w_time_record->hour()==15){
        init_time();
    }
    ui->w_time->display(w_time_record->toString("hh:mm:ss"));
}
void Widget::on_zhanghuxinxi_clicked()
{
    z0.show();
}


void Widget::on_tuichudenglu_clicked()
{
    close();
}


void Widget::on_chakangushi_clicked()
{

    g0.showit();
    g0.show();
}


void Widget::on_hangqing_clicked()
{
    h0.show();
}

