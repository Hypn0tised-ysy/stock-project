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
}

Widget::~Widget()
{
    delete ui;
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
    g0.show();
}


void Widget::on_hangqing_clicked()
{
    h0.show();
}

