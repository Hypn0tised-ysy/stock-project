#ifndef UI_SOLD_ORDER_H
#define UI_SOLD_ORDER_H

#include <QWidget>
#include <QDialog>
#include<QLineEdit>
#include "../implementation/Account.h"
namespace Ui {
class jiaoyi2;
}

class jiaoyi2 : public QWidget
{
    Q_OBJECT

public:
    jiaoyi2(Account *NowUser,QWidget *parent = nullptr);
    ~jiaoyi2();
    void resizeit();
signals:
    void send_it(QString ID,QString price,QString number,bool b_or_s);
private slots:

    void on_close_clicked();

    void on_queding_clicked();

private:
    Ui::jiaoyi2 *ui;
    Account *s_NowUser;
};

#endif // UI_SOLD_ORDER_H
