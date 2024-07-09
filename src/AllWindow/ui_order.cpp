#include "dingdan.h"
#include "ui_dingdan.h"
#include<vector>
#include<QString>
#include<QMessageBox>
dingdan::dingdan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dingdan)
{
    ui->setupUi(this);
    setFixedSize(600, 500);
    ui->deleteID->setClearButtonEnabled(true);
    resizeit();
}

dingdan::~dingdan()
{
    delete ui;
}

void dingdan::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.7,heights*0.85,widths*0.2,heights*0.1);
    ui->deleteID->setGeometry(widths*0.05,heights*0.85,widths*0.2,heights*0.1);
    ui->delete_2->setGeometry(widths*0.3,heights*0.85,widths*0.2,heights*0.1);
    ui->label->setGeometry(widths*0.05,heights*0.75,widths*0.2,heights*0.1);
    ui->tableWidget->setGeometry(widths*0.1,heights*0.1,widths*0.8,heights*0.6);
    ui->tableWidget->setColumnWidth(0,widths*0.2);
    ui->tableWidget->setColumnWidth(1,widths*0.2);
    ui->tableWidget->setColumnWidth(2,widths*0.15);
    ui->tableWidget->setColumnWidth(3,widths*0.2);

}







void dingdan::on_close_clicked()
{
    close();
}
std::vector<QString> vID;
std::vector<QString> vprice;
std::vector<QString> vnumber;
std::vector<bool> vb_or_s;
void dingdan::get_it(QString ID,QString price,QString number,bool b_or_s){
    vID.push_back(ID);
    vprice.push_back(price);
    vnumber.push_back(number);
    vb_or_s.push_back(b_or_s);
}



void dingdan::showit()
{
    ui->tableWidget->setRowCount(vID.size());
    for(int i=0;i<vID.size();i++){
        QString s1,s2,s3,s4;
        s1=vID[i];
        QTableWidgetItem *item=new QTableWidgetItem(s1);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,0,item);
        s2=vprice[i];
        item=new QTableWidgetItem(s2);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,1,item);
        s4=vnumber[i];
        item=new QTableWidgetItem(s4);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,3,item);
        bool bs=vb_or_s[i];
        if(bs)
            s3="买入";
        else s3="卖出";
        item=new QTableWidgetItem(s3);
        item->setFlags(Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,2,item);
    }
}
void dingdan::on_delete_2_clicked()
{   int k=-1;
    QString tmp=ui->deleteID->text();
    for(int i=0;i<vID.size();i++){
        if(vID[i]==tmp)
        {   k=i;
            break;}
    }
    if(k==-1)
    {
        QMessageBox::information(this,"警告","未找到相应订单",QMessageBox::Close);
        ui->deleteID->clear();
        return;
    }
    else {
        vID.erase(vID.begin()+k);
        vprice.erase(vprice.begin()+k);
        vnumber.erase(vnumber.begin()+k);
        vb_or_s.erase(vb_or_s.begin()+k);
        QMessageBox::information(this,"提示","订单已删除",QMessageBox::Close);
        ui->deleteID->clear();
        showit();
    }
}
