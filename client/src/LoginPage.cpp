#include "LoginPage.hpp"
#include <iostream>

Client::GUI::LoginPage::LoginPage(QWidget *parent) : APage(parent)
{
    setFixedSize(200, 100);

    _usernameForm = std::make_unique<QLineEdit>();
    _passwordForm = std::make_unique<QLineEdit>();

    _formLayout = std::make_unique<QFormLayout>();
    _formLayout->addRow("Username", _usernameForm.get());
    _formLayout->addRow("Password", _passwordForm.get());
    this->setLayout(layout.get());
    this->setObjectName("TOTO");
    std::cout << "Nom: "<< this->objectName().toStdString() << std::endl;

    //m_slider = new QSlider(Qt::Horizontal, this);
    //m_slider->setRange(200, 600);
    //m_slider->setGeometry(10, 60, 150, 20);

    //QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changeWidth(int)));
    // ? (Component qui send le signal, signal type, component qui reçoit le signal, slot fonction)
    //TODO: id de l'objet cliqué
    QObject::connect(_usernameForm.get(), SIGNAL(textChanged(QString)), this, SLOT(changeUsername(QString)));
}

void Client::GUI::LoginPage::initConnections()
{
    //QObject::connect(.get(), SIGNAL(buttonPush(QString)), parent, SLOT(changePage(QString)));
}

void Client::GUI::LoginPage::changeWidth(int width)
{
    this->setFixedSize(width, 100);
}



void Client::GUI::LoginPage::changeUsername(QString username)
{
    this->username = username.toStdString();
}

#include "moc_LoginPage.cpp"