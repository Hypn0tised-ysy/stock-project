#ifndef TRADE_DETAILS_H
#define TRADE_DETAILS_H

#include <QWidget>

namespace Ui {
class trade_details;
}

class trade_details : public QWidget
{
    Q_OBJECT

public:
    explicit trade_details(QWidget *parent = nullptr);
    ~trade_details();

private slots:
    void on_pushButton_clicked();

private:
    Ui::trade_details *ui;
};

#endif // TRADE_DETAILS_H
