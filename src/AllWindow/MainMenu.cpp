#include "Mainmenu.h"
#include "ui_Mainmenu.h"
#include "zhanghu.h"
#include "ui_zhanghu.h"
#include "gushi.h"
#include "ui_gushi.h"
#include "jiaoyi.h"
#include "ui_jiaoyi.h"
#include "hangqing.h"
#include "ui_hangqing.h"
MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_zhanghuxinxi_clicked()
{
    z0.show();
}

void MainMenu::on_tuichudenglu_clicked()
{
    close();
}

void MainMenu::on_chakangushi_clicked()
{
    g0.show();
}

void MainMenu::on_hangqing_clicked()
{
    h0.show();
}
