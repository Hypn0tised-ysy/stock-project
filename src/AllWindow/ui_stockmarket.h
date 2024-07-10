#ifndef UI_STOCKMARKET_H
#define UI_STOCKMARKET_H
#include"stockdetails.h"
#include"ui_stockdetails.h"
#include <QWidget>
#include <QDialog>
#include<QTime>
#include<QTimer>
namespace Ui {
class gushi;
}

class gushi : public QWidget
{
    Q_OBJECT
    enum colnum{ID=0,gongsi,gujia,gushu };
public:
    explicit gushi(QWidget *parent = nullptr);
    ~gushi();
    void resizeit();
signals:
    void send(int i);
    void send1(QString ID);
    void send2(QString price);
    void send3(QString number);

public slots:
    void showit();

private slots:
    void on_close_clicked();

    void init_time();

    void update_time();

    void on_show_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::gushi *ui;
    QTime *time_record;
    QTimer *timer;
};

#endif // UI_STOCKMARKET_H

