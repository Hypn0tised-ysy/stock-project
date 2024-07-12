#ifndef UI_SOLD_ORDER_H
#define UI_SOLD_ORDER_H

#include <QWidget>
#include <QDialog>
#include<QLineEdit>
#include "../implementation/Account.h"
#include "../implementation/stock.h"
namespace Ui {
class jiaoyi2;
}

class jiaoyi2 : public QWidget
{
    Q_OBJECT

public:
    jiaoyi2(QWidget *parent = nullptr);
    ~jiaoyi2();
    void resizeit();
signals:

private slots:

    void on_close_clicked();

    void on_queding_clicked();

private:
    Ui::jiaoyi2 *ui;
};

#endif // UI_SOLD_ORDER_H
