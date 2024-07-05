#include "hangqing.h"
#include "ui_hangqing.h"

hangqing::hangqing(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::hangqing)
{
    ui->setupUi(this);
}

hangqing::~hangqing()
{
    delete ui;
}

void hangqing::on_close_clicked()
{
    close();
}

