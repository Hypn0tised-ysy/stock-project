#include "dingdan.h"
#include "ui_dingdan.h"

dingdan::dingdan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dingdan)
{
    ui->setupUi(this);
}

dingdan::~dingdan()
{
    delete ui;
}

void dingdan::on_close_clicked()
{
    close();
}
///

