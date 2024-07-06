#include "jiaoyi2.h"
#include "ui_jiaoyi2.h"
#include<QMessageBox>
jiaoyi2::jiaoyi2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::jiaoyi2)
{
    ui->setupUi(this);
    ui->ID->setClearButtonEnabled(true);
    ui->jiage->setClearButtonEnabled(true);
    ui->num->setClearButtonEnabled(true);
}

jiaoyi2::~jiaoyi2()
{
    delete ui;
}




void jiaoyi2::on_close_clicked()
{
    close();
}


void jiaoyi2::on_queding_clicked()
{
    if(ui->ID->text()==""||ui->jiage->text()==""||ui->num->text()=="")
        QMessageBox::information(this,"警告","订单信息不全",QMessageBox::Close);
    else {
        QString ID=ui->ID->text();
        QString price=ui->jiage->text();
        QString number=ui->num->text();
        bool b_or_s=false;
        emit send_it(ID,price,number,b_or_s);
        ui->ID->clear();
        ui->jiage->clear();
        ui->num->clear();
        QMessageBox::information(this,"提示","订单已提交",QMessageBox::Close);
        close();
    }
}


