#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <string>
#include <QVBoxLayout>
const std::string LINEEDITSTYLE = "QLineEdit{border: 2px solid #8f8f91; border-radius: 10px; padding: 8px; background-color: #f2f2f2;}"
                                  "QLineEdit:focus{border: 2px solid #4d90fe;}"
                                  "QLineEdit:hover{border: 2px solid #4d90fe;}"
                                  "QLineEdit:disabled{background-color: #d9d9d9;}";
const std::string BUTTONSTYLE = "QPushButton{background-color: #4d90fe; color: white; border: none; border-radius: 10px; padding: 8px;}"
                                "QPushButton:hover{background-color: #357ae8;}"
                                "QPushButton:pressed{background-color: #135cbf;}";
class LoginWindow : public QMainWindow
{
    Q_OBJECT
    QStackedWidget *MainWindowStack;

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLineEdit *UserNameLineEdit;
    QLineEdit *PasswordLineEdit;
    QPushButton *LoginButton;
    QPushButton *RegisterButton;
    QWidget *CentralWidget;
    QVBoxLayout *CentralLayout = nullptr;
    QLabel *TitleLabel;
};