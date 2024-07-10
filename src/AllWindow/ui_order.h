#ifndef UI_ORDER_H
#define UI_ORDER_H

#include <QWidget>
#include "../implementation/Account.h"
#include "../implementation/order.h"
namespace Ui {
class dingdan;
}

class dingdan : public QWidget
{
    Q_OBJECT
    enum cloum{ID=0,jiage,xingzhi,num};
public:
    dingdan(Account *NowUser,QWidget *parent = nullptr);
    ~dingdan();
    void resizeit();
public slots:
    void showit();
    void get_it(QString ID,QString price,QString number,bool b_or_s);
private slots:
    void on_close_clicked();

    void on_delete_2_clicked();


    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::dingdan *ui;
    Account* o_NowUser;
    int delete_ID=-1;
};

#endif // UI_ORDER_H
