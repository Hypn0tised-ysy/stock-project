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
MainMenu::MainMenu(Account *_NowUser, QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    NowUser = _NowUser;
    ui->setupUi(this);
    setFixedSize(1500, 800);
    w_timer = new QTimer;
    w_time_record = new QTime;
    ui->times->setDigitCount(8);
    init_time();
    w_timer->start(100);
    connect(w_timer, SIGNAL(timeout()), this, SLOT(update_time()));
    init();
    resizeit();
}

MainMenu::~MainMenu()
{
    delete ui;
}
void MainMenu::init()
{
    QString s_username=QString::fromStdString(NowUser->return_username());
    ui->name->setText(s_username);
    QString s_id=QString::fromStdString(std::to_string(NowUser->return_id()));
    ui->ID->setText(s_id);

}

void MainMenu::init_time()
{
    w_time_record->setHMS(0, 8, 0);
    ui->times->display(w_time_record->toString("hh:mm:ss"));
}

void MainMenu::update_time()
{
    *w_time_record = w_time_record->addSecs(1);
    if (w_time_record->hour() == 15)
    {
        init_time();
    }
    ui->times->display(w_time_record->toString("hh:mm:ss"));
}

void MainMenu::on_zhanghuxinxi_clicked()
{
    //Account* NowUsers=NowUser;
    //z0.get_account(NowUsers);
    z0.show();
}

void MainMenu::on_tuichudenglu_clicked()
{
    emit tuichudenglu();
    close();
}

void MainMenu::on_chakangushi_clicked()
{
    g0.showit();
    g0.show();
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
    ui->times->setGeometry(widths * 0.7, heights * 0.1, widths * 0.1, heights * 0.05);
    // 位置重设；
}
