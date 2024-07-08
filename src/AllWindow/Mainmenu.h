#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QWidget>
#include "zhanghu.h"
#include "ui_zhanghu.h"
#include "gushi.h"
#include "ui_gushi.h"
#include "hangqing.h"
#include "ui_hangqing.h"
#include <QProgressBar>
#include <QMessageBox>
#include <QPushButton>
#include "../implementation/Account.h"
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

private slots:

    void on_zhanghuxinxi_clicked();

    void on_tuichudenglu_clicked();

    void on_chakangushi_clicked();

    void on_hangqing_clicked();

    void init_time();

    void update_time();

private:
    Ui::Widget *ui;
    zhanghu z0;
    gushi g0;
    hangqing h0;
    QTime *w_time_record;
    QTimer *w_timer;
    Account *NowUser;
};
#endif // WIDGET_H
