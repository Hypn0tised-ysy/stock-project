#ifndef ZHANGHU_H
#define ZHANGHU_H

#include <QWidget>
#include <QDialog>
#include"jiaoyi.h"
#include"ui_jiaoyi.h"
#include"jiaoyi2.h"
#include"ui_jiaoyi2.h"
#include"dingdan.h"
#include"ui_dingdan.h"
namespace Ui {
class zhanghu;
}

class zhanghu : public QWidget
{
    Q_OBJECT

public:
    explicit zhanghu(QWidget *parent = nullptr);
    ~zhanghu();

private slots:
    void on_tuichu_clicked();

    void on_buy_clicked();

    void on_sold_clicked();

    void on_check_dingdan_clicked();

private:
    Ui::zhanghu *ui;
    jiaoyi j0;
    jiaoyi2 j1;
    dingdan d0;
};

#endif // ZHANGHU_H
