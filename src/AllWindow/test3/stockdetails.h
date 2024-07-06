#ifndef STOCKDETAILS_H
#define STOCKDETAILS_H

#include <QWidget>

namespace Ui {
class StockDetails;
}

class StockDetails : public QWidget
{
    Q_OBJECT

public:
    explicit StockDetails(QWidget *parent = nullptr);
    ~StockDetails();
public slots:
    void get(int i);
    void get1(QString ID);
    void get2(QString price);
    void get3(QString number);
    void showit();
private slots:
    void on_close_clicked();

private:
    Ui::StockDetails *ui;
};

#endif // STOCKDETAILS_H
