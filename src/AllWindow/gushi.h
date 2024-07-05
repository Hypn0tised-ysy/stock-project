#ifndef GUSHI_H
#define GUSHI_H

#include <QWidget>
#include <QDialog>

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

private slots:
    void on_close_clicked();

    void on_show_clicked();

private:
    Ui::gushi *ui;

};

#endif // GUSHI_H
