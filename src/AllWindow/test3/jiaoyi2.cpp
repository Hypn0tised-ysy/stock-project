#include "jiaoyi2.h"
#include "ui_jiaoyi2.h"

jiaoyi2::jiaoyi2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::jiaoyi2)
{
    ui->setupUi(this);
}

jiaoyi2::~jiaoyi2()
{
    delete ui;
}

void jiaoyi2::on_pushButton_2_clicked()
{
    close();
}

