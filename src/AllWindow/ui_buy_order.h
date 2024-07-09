#ifndef JIAOYI_H
#define JIAOYI_H

#include <QWidget>
#include <QDialog>
#include<QLineEdit>
namespace Ui {
class jiaoyi;
}

class jiaoyi : public QWidget
{
    Q_OBJECT

public:
    explicit jiaoyi(QWidget *parent = nullptr);
    ~jiaoyi();
    void resizeit();
signals:
    void send_it(QString ID,QString price,QString number,bool b_or_s);
private slots:


    void on_queding_clicked();

    void on_close_clicked();

private:
    Ui::jiaoyi *ui;
};

#endif // JIAOYI_H
