#ifndef UI_BUY_ORDER_H
#define UI_BUY_ORDER_H

#include <QWidget>
#include <QDialog>
#include<QLineEdit>
#include "../implementation/Account.h"
#include "../implementation/stock.h"
#include "../implementation/order.h"
namespace Ui {
class jiaoyi;
}

class jiaoyi : public QWidget
{
    Q_OBJECT

public:
    jiaoyi(QWidget *parent = nullptr);
    ~jiaoyi();
    void resizeit();
signals:

private slots:


    void on_queding_clicked();

    void on_close_clicked();

private:
    Ui::jiaoyi *ui;
};

#endif // UI_BUY_ORDER_H
