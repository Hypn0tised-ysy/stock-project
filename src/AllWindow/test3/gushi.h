#ifndef GUSHI_H
#define GUSHI_H

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
public slots:
    void showit();
private slots:
    void on_close_clicked();
    void init_time();
    void update_time();


    void on_pushButton_clicked();

private:
    Ui::gushi *ui;
    QTime *time_record;
    QTimer *timer;
};

#endif // GUSHI_H
