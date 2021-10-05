/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** MainWindow
*/

#include "MainWindow.hpp"
#include "APage.hpp"

using namespace Client::GUI;

MainWindow::MainWindow() : _pages(this), _tcpClient("10.19.253.225", 5000)
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
    //parserCommand
    if (msg.toStdString() == "yes")
        emit validSignalResponse("", "");
    else
        emit wrongSignalResponse("wrong pass", "wrong user");
}

void MainWindow::changeCurrentPage(pageNames name)
{
    _pages.setCurrentPage(name);
}

void MainWindow::checkSignal(ClientInfos infos, signal_e e)
{
    std::cout << infos.username << std::endl;
    std::cout << infos.password << std::endl;

    _tcpClient.send(infos.username);
    if (true)
        emit validSignalResponse("", "");
    else
        emit wrongSignalResponse("wrong pass", "wrong user");
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
    QObject::connect(_pages.getPage(LOGIN), SIGNAL(checkSignIn(ClientInfos, signal_e)),
        this, SLOT(checkSignal(ClientInfos, signal_e)));

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
