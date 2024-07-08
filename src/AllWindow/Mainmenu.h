#ifndef WIDGET_H
#define WIDGET_H

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
    MainMenu(Account InputAccount, QWidget *parent = nullptr);
    ~MainMenu();

private slots:

    void on_zhanghuxinxi_clicked();

    void on_tuichudenglu_clicked();

    void on_chakangushi_clicked();

    void on_hangqing_clicked();

private:
    Account NowAccount;
    Ui::Widget *ui;
    zhanghu z0;
    gushi g0;
    hangqing h0;
};
#endif // WIDGET_H
