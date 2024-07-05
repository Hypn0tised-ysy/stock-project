#include "jiaoyi.h"
#include "ui_jiaoyi.h"

jiaoyi::jiaoyi(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::jiaoyi)
{
    ui->setupUi(this);
}

jiaoyi::~jiaoyi()
{
    delete ui;
}

void jiaoyi::on_pushButton_2_clicked()
{
    close();
}

