#include "jiaoyi2.h"
#include "ui_jiaoyi2.h"
#include<QMessageBox>
jiaoyi2::jiaoyi2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::jiaoyi2)
{
    ui->setupUi(this);
    setFixedSize(500, 600);
    ui->ID->setClearButtonEnabled(true);
    ui->jiage->setClearButtonEnabled(true);
    ui->num->setClearButtonEnabled(true);
    resizeit();
}

jiaoyi2::~jiaoyi2()
{
    delete ui;
}


void jiaoyi2::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.6,heights*0.85,widths*0.3,heights*0.1);
    ui->queding->setGeometry(widths*0.1,heights*0.85,widths*0.3,heights*0.1);
    ui->ID->setGeometry(widths*0.2,heights*0.2,widths*0.6,heights*0.1);
    ui->label->setGeometry(widths*0.2,heights*0.1,widths*0.6,heights*0.1);
    ui->jiage->setGeometry(widths*0.2,heights*0.4,widths*0.6,heights*0.1);
    ui->label_2->setGeometry(widths*0.2,heights*0.3,widths*0.6,heights*0.1);
    ui->num->setGeometry(widths*0.2,heights*0.6,widths*0.6,heights*0.1);
    ui->label_3->setGeometry(widths*0.2,heights*0.5,widths*0.6,heights*0.1);
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


