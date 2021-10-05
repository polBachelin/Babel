/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** MainWindow
*/

#include "MainWindow.hpp"
#include "APage.hpp"

using namespace Client::GUI;

MainWindow::MainWindow() : _pages(this), _tcpClient("localhost", 6637)
{
    this->setFixedSize({WIDTH, HEIGHT});
    setWindowTitle("Babel");
    this->setCentralWidget(&_pages);
    this->setStyleSheet(
        "background-image:url("
        BACKGROUND_PATH
        "); background-position: center;");

    initConnections();
}

MainWindow::~MainWindow()
{
    std::cout << "MainWindow détruit" << std::endl;
}

void MainWindow::receivedSomething(QString msg)
{
    std::cout << "Message" << msg.toStdString() << std::endl;
}


void MainWindow::changeCurrentPage(pageNames name)
{
    _pages.setCurrentPage(name);
}

void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    std::string strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }
    std::cout << strError << std::endl;
}

void MainWindow::initConnections(void)
{
    QObject::connect(
        _pages.getPage(LOGIN), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
    QObject::connect(
        _pages.getPage(REGISTER), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
    QObject::connect(
        _pages.getPage(CALL), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
    QObject::connect(
        _pages.getPage(CONTACTS), SIGNAL(changePage(pageNames)),
        this, SLOT(changeCurrentPage(pageNames)));
    QObject::connect(&_tcpClient, &Client::Network::TcpClient::dataAvailable, this, &MainWindow::receivedSomething);
    QObject::connect(_tcpClient.getSocket(), SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));
}

#include "moc_MainWindow.cpp"
