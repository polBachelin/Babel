#include "NextPage.hpp"
#include <iostream>

Client::GUI::NextPage::NextPage(ClientInfos infos, QWidget *parent) : APage(infos, parent)
{
    setFixedSize(200, 100);

    _backButton = std::make_unique<QPushButton>("go Back");
    _formLayout = std::make_unique<QFormLayout>();
    _formLayout->addRow(_backButton.get());


    this->setLayout(_formLayout.get());
    this->setObjectName("NextPage");

    // ? (Component qui send le signal, signal type, component qui reçoit le signal, slot fonction)
    initConnections();
}

Client::GUI::NextPage::~NextPage()
{
    std::cout << "NextPage détruit" << std::endl;
}


void Client::GUI::NextPage::initConnections()
{
    QObject::connect(_backButton.get(), SIGNAL(clicked()), this, SLOT(goBack()));
}

void Client::GUI::NextPage::goBack()
{
    emit changePage(LOGIN);
}

#include "moc_NextPage.cpp"