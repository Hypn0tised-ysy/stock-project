#ifndef HANGQING_H
#define HANGQING_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class hangqing;
}

class hangqing : public QWidget
{
    Q_OBJECT

public:
    explicit hangqing(QWidget *parent = nullptr);
    ~hangqing();
     void resizeit();
private slots:
    void on_close_clicked();

private:
    Ui::hangqing *ui;
};

#endif // HANGQING_H
