#include "Mainmenu.h"
#include "ui_Mainmenu.h"
#include "ui_account.h"
#include "ui_ui_account.h"
#include "ui_stockmarket.h"
#include "ui_ui_stockmarket.h"
#include "ui_buy_order.h"
#include "ui_ui_buy_order.h"
#include "hangqing.h"
#include "ui_hangqing.h"

#include "../implementation/Account.h"
extern Database db;
Account *real_NowUser;
std::map<std::string, Stock> mp1;
std::vector<Stock> all_stocks;
MainMenu::MainMenu(Account *_NowUser, QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    real_NowUser = _NowUser;
    init_stocks();
    z0=new zhanghu(nullptr);
    g0=new gushi(nullptr);
    z0->mp1=mp1;
    ui->setupUi(this);
    g0->all_stocks=all_stocks;
    setFixedSize(1500, 800);
    w_timer = new QTimer;
    w_timer->start(10);
    connect(w_timer, SIGNAL(timeout()), this, SLOT(update_ticks()));
    init();
    resizeit();
}

MainMenu::~MainMenu()
{
    delete ui;
}
void MainMenu::init()
{
    QString s_username=QString::fromStdString(real_NowUser->return_username());
    ui->name->setText(s_username);
    QString s_id=QString::fromStdString(std::to_string(real_NowUser->return_id()));
    ui->ID->setText(s_id);
    for(int i=0;i<all_stocks.size();i++)
    {
        std::vector<Order> tmp1=db.getOrdersList(QString::fromStdString(all_stocks[i].symbol),true);
        std::vector<Order> tmp2=db.getOrdersList(QString::fromStdString(all_stocks[i].symbol),false);
        for(int j=0;j<tmp1.size();j++){
            mp1[all_stocks[i].symbol].add_order(tmp1[j]);
        }
        for(int k=0;k<tmp2.size();k++){
            mp1[all_stocks[i].symbol].add_order(tmp2[k]);
        }
    }
}
void MainMenu::init_stocks()
{
    all_stocks=db.getStocksList();
    mp1=BuildStockMap(all_stocks);
}


void MainMenu::update_ticks(){
    int times=ticks_time(5000,0);
    if(times){
        ticks+=times;
        g0->showit();
        z0->showit();
        ui->ticks->setText(QString::fromStdString(std::to_string(ticks)));
        /*for(int i=0;i<all_stocks.size();i++)
        {
            std::vector<Order> tmp1=db.getOrdersList(QString::fromStdString(all_stocks[i].symbol),true);
            std::vector<Order> tmp2=db.getOrdersList(QString::fromStdString(all_stocks[i].symbol),false);
            for(int j=0;j<tmp1.size();j++){
                all_stocks[i].add_order(tmp1[j]);
            }
            for(int k=0;k<tmp2.size();k++){
                all_stocks[i].add_order(tmp2[k]);
            }
        }*/
    }
    else
        return;

}

void MainMenu::on_zhanghuxinxi_clicked()
{
    z0->showit();
    z0->show();
}

void MainMenu::on_tuichudenglu_clicked()
{
    close();
    emit tuichudenglu();
}

void MainMenu::on_chakangushi_clicked()
{
    g0->show();
    g0->tips();
}

void MainMenu::on_hangqing_clicked()
{
    h0.show();
}

void MainMenu::resizeit()
{
    int widths = this->width();
    int heights = this->height();
    ui->chakangushi->setGeometry(widths * 0.55, heights * 0.7, widths * 0.2, heights * 0.1);
    ui->hangqing->setGeometry(widths * 0.55, heights * 0.85, widths * 0.2, heights * 0.1);
    ui->zhanghuxinxi->setGeometry(widths * 0.25, heights * 0.7, widths * 0.2, heights * 0.1);
    ui->tuichudenglu->setGeometry(widths * 0.25, heights * 0.85, widths * 0.2, heights * 0.1);
    ui->name->setGeometry(widths * 0.3, heights * 0.55, widths * 0.4, heights * 0.1);
    ui->name1->setGeometry(widths * 0.4, heights * 0.5, widths * 0.2, heights * 0.05);
    ui->ID->setGeometry(widths * 0.3, heights * 0.4, widths * 0.4, heights * 0.1);
    ui->ID1->setGeometry(widths * 0.4, heights * 0.35, widths * 0.2, heights * 0.05);
    ui->label->setGeometry(widths * 0.4, heights * 0.1, widths * 0.2, heights * 0.2);
    ui->ticks->setGeometry(widths * 0.7, heights * 0.1, widths * 0.1, heights * 0.05);
    // 位置重设；
}
