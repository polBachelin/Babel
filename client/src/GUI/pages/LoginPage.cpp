#include "LoginPage.hpp"
#include <iostream>

Client::GUI::LoginPage::LoginPage(Client::ClientInfos infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(200, 100);

    _usernameForm = std::make_unique<QLineEdit>();
    _passwordForm = std::make_unique<QLineEdit>();
    _signButton = std::make_unique<QPushButton>("Sign In");
    _formLayout = std::make_unique<QFormLayout>();

    _formLayout->addRow("Username", _usernameForm.get());
    _formLayout->addRow("Password", _passwordForm.get());
    _formLayout->addRow(_signButton.get());


    this->setLayout(_formLayout.get());
    this->setObjectName("TOTO");
    std::cout << "Nom: "<< this->objectName().toStdString() << std::endl;

    initConnections();
}

void Client::GUI::LoginPage::initConnections()
{
    QObject::connect(_usernameForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changeUsername(QString)));
    QObject::connect(_signButton.get(), SIGNAL(clicked()), this, SLOT(signIn()));
}



void Client::GUI::LoginPage::changeWidth(int width)
{
    this->setFixedSize(width, 100);
}

void Client::GUI::LoginPage::changeUsername(QString username)
{
    this->username = username.toStdString();
}

void Client::GUI::LoginPage::signIn()
{
    emit changePage(NEXT);
}

#include "moc_LoginPage.cpp"