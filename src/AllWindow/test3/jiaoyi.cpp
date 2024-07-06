#include "jiaoyi.h"
#include "ui_jiaoyi.h"
#include<QMessageBox>
jiaoyi::jiaoyi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::jiaoyi)
{
    ui->setupUi(this);

    ui->ID->setClearButtonEnabled(true);
    ui->jiage->setClearButtonEnabled(true);
    ui->num->setClearButtonEnabled(true);
}

jiaoyi::~jiaoyi()
{
    delete ui;
}

void jiaoyi::on_close_clicked()
{
    close();
}

void jiaoyi::on_queding_clicked()
{
    if(ui->ID->text()==""||ui->jiage->text()==""||ui->num->text()=="")
        QMessageBox::information(this,"警告","订单信息不全",QMessageBox::Close);
    else {
        QString ID=ui->ID->text();
        QString price=ui->jiage->text();
        QString number=ui->num->text();
        bool b_or_s=true;
        emit send_it(ID,price,number,b_or_s);
        ui->ID->clear();
        ui->jiage->clear();
        ui->num->clear();
        QMessageBox::information(this,"提示","订单已提交",QMessageBox::Close);
        close();
    }

}

