#ifndef DINGDAN_H
#define DINGDAN_H

#include <QWidget>

namespace Ui {
class dingdan;
}

class dingdan : public QWidget
{
    Q_OBJECT
    enum cloum{ID=0,jiage,xingzhi,num};
public:
    explicit dingdan(QWidget *parent = nullptr);
    ~dingdan();
    void resizeit();
public slots:
    void showit();
    void get_it(QString ID,QString price,QString number,bool b_or_s);
private slots:
    void on_close_clicked();

    void on_delete_2_clicked();


private:
    Ui::dingdan *ui;
};

#endif // DINGDAN_H
