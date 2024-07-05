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

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::jiaoyi2 *ui;
};

#endif // JIAOYI2_H
