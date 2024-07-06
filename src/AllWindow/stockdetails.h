#ifndef STOCKDETAILS_H
#define STOCKDETAILS_H

#include <QWidget>

namespace Ui {
class stockdetails;
}

class stockdetails : public QWidget
{
    Q_OBJECT

public:
    explicit stockdetails(QWidget *parent = nullptr);
    ~stockdetails();
    void get(int i);
    void get1(QString ID);
    void get2(QString price);
    void get3(QString number);
    void showit();
private slots:
    void on_close_clicked();

private:
    Ui::stockdetails *ui;
};

#endif // STOCKDETAILS_H
