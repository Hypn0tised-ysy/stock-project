#include "ui_buy_order.h"
#include "ui_ui_buy_order.h"
#include<QMessageBox>
#include"Mainmenu.h"
extern Account* real_NowUser;
extern std::map<std::string, Stock> mp1;
extern std::vector<Stock> all_stocks;
extern Database db;
jiaoyi::jiaoyi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::jiaoyi)
{
    ui->setupUi(this);
    setFixedSize(500, 600);
    ui->ID->setClearButtonEnabled(true);
    ui->jiage->setClearButtonEnabled(true);
    ui->num->setClearButtonEnabled(true);
    resizeit();
}

jiaoyi::~jiaoyi()
{
    delete ui;
}

void jiaoyi::resizeit(){
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

void jiaoyi::on_queding_clicked()
{
        if(ui->ID->text()==""||ui->jiage->text()==""||ui->num->text()=="")
            QMessageBox::information(this,"警告","订单信息不全",QMessageBox::Close);
        else {
            QString ID=ui->ID->text();
            QString price=ui->jiage->text();
            QString number=ui->num->text();
            int tmp1=real_NowUser->return_id();
            int order_id=real_NowUser->add_my_order(tmp1,price.toDouble(),number.toInt(),ID,false);
            if(order_id<=0)
            {
                QMessageBox::information(this,"警告","订单信息有误，请您再次检查",QMessageBox::Close);
                return;
            }
            else{
            ui->ID->clear();
            ui->jiage->clear();
            ui->num->clear();
            QMessageBox::information(this,"提示","订单已提交",QMessageBox::Close);
            std::string id=ID.toStdString();
            double prices=price.toDouble();
            int numbers=number.toInt();
            std::string peo_id=std::to_string(real_NowUser->return_id());
            Order order(order_id,peo_id,prices,numbers,id,false);
            mp1[id].add_order(order);
            /*for(int i=0;i<all_stocks.size();i++)
            {
                std::vector<Order> tmp1=db.getOrdersList(QString::fromStdString(all_stocks[i].symbol),true);
                std::vector<Order> tmp2=db.getOrdersList(QString::fromStdString(all_stocks[i].symbol),false);
                for(int j=0;j<tmp1.size();j++){
                    mp1[all_stocks[i].symbol].add_order(tmp1[j]);
                }
                for(int k=0;k<tmp2.size();k++){
                    mp1[all_stocks[i].symbol].add_order(tmp2[k]);
                }
            }*/
            close();
            }
        }

}


void jiaoyi::on_close_clicked()
{
    ui->ID->clear();
    ui->jiage->clear();
    ui->num->clear();
    close();
}

