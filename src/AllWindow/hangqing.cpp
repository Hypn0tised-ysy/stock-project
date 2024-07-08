#include "hangqing.h"
#include "ui_hangqing.h"

hangqing::hangqing(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hangqing)
{
    ui->setupUi(this);
    setFixedSize(1500, 800);
    resizeit();
}

hangqing::~hangqing()
{
    delete ui;
}

void hangqing::on_close_clicked()
{
    close();
}
void hangqing::resizeit(){
    int widths=this->width();
    int heights=this->height();
    ui->close->setGeometry(widths*0.7,heights*0.8,widths*0.15,heights*0.1);
    ui->tableWidget->setGeometry(widths*0.1,heights*0.2,widths*0.8,heights*0.55);
    ui->label->setGeometry(widths*0.1,heights*0.05,widths*0.15,heights*0.1);

}
