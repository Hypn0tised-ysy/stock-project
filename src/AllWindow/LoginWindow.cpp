#include "LoginWindow.h"
#include <QVBoxLayout>
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    CentralWidget = new QWidget(this);
    UserNameLineEdit = new QLineEdit(this);
    PasswordLineEdit = new QLineEdit(this);
    TitleLabel = new QLabel("模拟股票交易", this);
    TitleLabel->setStyleSheet("font-size: 48px; font-weight: bold;");
    TitleLabel->setFixedSize(TitleLabel->sizeHint());
    QFont font = UserNameLineEdit->font();
    font.setPointSize(24);
    UserNameLineEdit->setFont(font);
    PasswordLineEdit->setFont(font);
    UserNameLineEdit->setStyleSheet(QString::fromStdString(LINEEDITSTYLE));
    PasswordLineEdit->setStyleSheet(QString::fromStdString(LINEEDITSTYLE));
    UserNameLineEdit->setPlaceholderText("User Name");
    PasswordLineEdit->setPlaceholderText("Password");
    LoginButton = new QPushButton("Login", this);
    RegisterButton = new QPushButton("Register", this);
    LoginButton->setStyleSheet(QString::fromStdString(BUTTONSTYLE));
    CentralLayout = new QVBoxLayout(CentralWidget);
    RegisterButton->setStyleSheet(QString::fromStdString(BUTTONSTYLE));
    resizeEvent(nullptr);
    LoginButton->setFont(font);
    RegisterButton->setFont(font);
    PasswordLineEdit->setEchoMode(QLineEdit::Password);
    auto LineEditLayout = new QVBoxLayout();
    auto ButtonLayout = new QHBoxLayout();
    auto UserNameLayout = new QHBoxLayout();
    UserNameLayout->addStretch();
    UserNameLayout->addWidget(UserNameLineEdit);
    UserNameLayout->addStretch();
    auto PasswordLayout = new QHBoxLayout();
    PasswordLayout->addStretch();
    PasswordLayout->addWidget(PasswordLineEdit);
    PasswordLayout->addStretch();
    auto TitleLayout = new QHBoxLayout();
    TitleLayout->addStretch();
    TitleLayout->addWidget(TitleLabel);
    TitleLayout->addStretch();
    LineEditLayout->addLayout(UserNameLayout);
    LineEditLayout->addLayout(PasswordLayout);
    ButtonLayout->addWidget(LoginButton);
    ButtonLayout->addWidget(RegisterButton);
    CentralLayout->addLayout(TitleLayout);
    int desiredHeight = static_cast<int>(this->height() * 0.1);
    CentralLayout->addLayout(LineEditLayout);
    CentralLayout->addLayout(ButtonLayout);
    CentralWidget->setLayout(CentralLayout);
    setCentralWidget(CentralWidget);
    connect(RegisterButton, &QPushButton::clicked, this, [this]()
            {
                std::string Username = UserNameLineEdit->text().toStdString();
                std::string Password = PasswordLineEdit->text().toStdString();
                if (Username.empty() || Password.empty())
                {
                    QMessageBox::warning(this, "Warning", "Please enter your username and password.");
                    return;
                }
                // User=Userregstier(Username, password);
                if(true)
                {
                    emit Changepage();
                } });
    connect(LoginButton, &QPushButton::clicked, this, [this]()
            {
        std::string Username = UserNameLineEdit->text().toStdString();
        std::string Password = PasswordLineEdit->text().toStdString();
        if (Username.empty() || Password.empty())
        {
            QMessageBox::warning(this, "Warning", "Please enter your username and password.");
            return;
        }
        else
        {
            // User=Userlogin(Username, password);
            if (true)
            {
                emit Changepage();
            }
        } });
}
LoginWindow::~LoginWindow()
{
    delete UserNameLineEdit;
    delete PasswordLineEdit;
    delete LoginButton;
    delete RegisterButton;
    delete CentralWidget;
}
void LoginWindow::resizeEvent(QResizeEvent *event)
{
    int desiredWidth = static_cast<int>(this->width() * 0.1);
    int desiredHeight = static_cast<int>(this->height() * 0.1);
    UserNameLineEdit->setFixedSize(desiredWidth * 6, desiredHeight * 1.2);
    PasswordLineEdit->setFixedSize(desiredWidth * 6, desiredHeight * 1.2);
    LoginButton->setFixedSize(desiredWidth * 4, desiredHeight);
    RegisterButton->setFixedSize(desiredWidth * 4, desiredHeight);
}