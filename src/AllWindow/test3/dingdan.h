#ifndef DINGDAN_H
#define DINGDAN_H

#include <QWidget>

namespace Ui {
class dingdan;
}

class dingdan : public QWidget
{
    Q_OBJECT

public:
    explicit dingdan(QWidget *parent = nullptr);
    ~dingdan();

private slots:
    void on_close_clicked();

private:
    Ui::dingdan *ui;
};

#endif // DINGDAN_H
//