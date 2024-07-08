#include "trade_details.h"
#include "ui_trade_details.h"

trade_details::trade_details(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::trade_details)
{
    ui->setupUi(this);
    setFixedSize(600, 400);
    resizeit();
}

trade_details::~trade_details()
{
    delete ui;
}

void trade_details::resizeit()
{
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.4,heights*0.85,widths*0.2,heights*0.1);

    ui->label_9->setGeometry(widths*0.1,heights*0.5,widths*0.2,heights*0.2);
    ui->number->setGeometry(widths*0.35,heights*0.5,widths*0.2,heights*0.2);
    ui->label_11->setGeometry(widths*0.6,heights*0.5,widths*0.2,heights*0.2);
    ui->time->setGeometry(widths*0.85,heights*0.5,widths*0.2,heights*0.2);

    ui->label->setGeometry(widths*0.1,heights*0.1,widths*0.2,heights*0.2);
    ui->ID->setGeometry(widths*0.35,heights*0.1,widths*0.2,heights*0.2);
    ui->label_3->setGeometry(widths*0.6,heights*0.1,widths*0.2,heights*0.2);
    ui->buy_ID->setGeometry(widths*0.85,heights*0.1,widths*0.2,heights*0.2);

    ui->label_5->setGeometry(widths*0.1,heights*0.3,widths*0.2,heights*0.2);
    ui->b_or_s->setGeometry(widths*0.35,heights*0.3,widths*0.2,heights*0.2);
    ui->label_7->setGeometry(widths*0.6,heights*0.3,widths*0.2,heights*0.2);
    ui->price->setGeometry(widths*0.85,heights*0.3,widths*0.2,heights*0.2);

}



void trade_details::on_close_clicked()
{
    close();
}

