#ifndef JIAOYI2_H
#define JIAOYI2_H

#include <QWidget>
#include <QDialog>
namespace Ui {
class jiaoyi2;
}

class jiaoyi2 : public QWidget
{
    Q_OBJECT

public:
    explicit jiaoyi2(QWidget *parent = nullptr);
    ~jiaoyi2();
signals:
    void send_it(QString ID,QString price,QString number,bool b_or_s);
private slots:

    void on_close_clicked();

    void on_queding_clicked();

private:
    Ui::jiaoyi2 *ui;
};

#endif // JIAOYI2_H
