#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QWidget>
#include "ui_account.h"
#include "ui_ui_account.h"
#include "ui_stockmarket.h"
#include "ui_ui_stockmarket.h"
#include "hangqing.h"
#include "ui_hangqing.h"
#include <QProgressBar>
#include <QMessageBox>
#include <QPushButton>
#include "../implementation/Account.h"
#include "../implementation/stock.h"
#include "../implementation/StockMap.h"
#include "../database/database.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(Account *NowUser, QWidget *parent = nullptr);
    ~MainMenu();
    void resizeit();
public slots:
    void on_tuichudenglu_clicked();
signals:
    void tuichudenglu();
private slots:

    void on_zhanghuxinxi_clicked();

    void on_chakangushi_clicked();

    void on_hangqing_clicked();

    void init();

    void init_stocks();

    void update_ticks();
private:
    Ui::Widget *ui;
    zhanghu *z0;
    gushi *g0;
    hangqing h0;
    QTimer *w_timer;
    int ticks=0;
};
#endif // WIDGET_H
