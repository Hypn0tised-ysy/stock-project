#include "balance.h"
#include "ui_balance.h"

balance::balance(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::balance)
{
    ui->setupUi(this);
    setFixedSize(600, 500);
    resizeit();
}

balance::~balance()
{
    delete ui;
}
void balance::resizeit()
{
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.7,heights*0.85,widths*0.2,heights*0.1);
    ui->label_2->setGeometry(widths*0.7,heights*0.1,widths*0.2,heights*0.1);
    ui->textBrowser->setGeometry(widths*0.6,heights*0.25,widths*0.3,heights*0.1);
    ui->label->setGeometry(widths*0.1,heights*0.1,widths*0.2,heights*0.1);
    ui->tableWidget->setGeometry(widths*0.05,heights*0.25,widths*0.5,heights*0.6);

}
void balance::on_close_clicked()
{
    close();
}

