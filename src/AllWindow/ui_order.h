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
public:
    dingdan(QWidget *parent = nullptr);
    ~dingdan();
    void resizeit();
public slots:
    void showit();
private slots:
    void on_close_clicked();

    void on_delete_2_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::dingdan *ui;
    int delete_ID=-1;
    bool first=true;
};

#endif // UI_ORDER_H
