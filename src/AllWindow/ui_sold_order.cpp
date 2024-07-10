#include "ui_sold_order.h"
#include "ui_ui_sold_order.h"
#include<QMessageBox>
jiaoyi2::jiaoyi2(Account *_NowUser,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::jiaoyi2)
{   s_NowUser=_NowUser;
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
    ui->ID->clear();
    ui->jiage->clear();
    ui->num->clear();
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
        int tmp1=s_NowUser->return_id();
        int tmp=s_NowUser->add_my_order(tmp1,price.toDouble(),number.toInt(),ID,!b_or_s);
        if(tmp<=0)
        {
            QMessageBox::information(this,"警告","订单信息有误，请您再次检查",QMessageBox::Close);
            return;
        }
        else{
            emit send_it(ID,price,number,b_or_s);
            ui->ID->clear();
            ui->jiage->clear();
            ui->num->clear();
            QMessageBox::information(this,"提示","订单已提交",QMessageBox::Close);
            close();
        }
    }

}


