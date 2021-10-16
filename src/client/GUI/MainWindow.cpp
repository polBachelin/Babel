/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** MainWindow
*/

#include "MainWindow.hpp"
#include "APage.hpp"
#include <QNetworkInterface>
#include <QNetworkAddressEntry>

using namespace Client::GUI;

std::map<std::size_t, std::string> errSockMap = {
    {0, "!! ConnectionRefused Error !!"},
    {1, "!! RemoteHostClosed Error !!"},
    {2, "!! HostNotFound Error !!"},
    {3, "!! SocketAccess Error !!"},
    {4, "!! SocketResource Error !!"},
    {5, "!! SocketTimeout Error !!"},
    {6, "!! DatagramTooLarge Error !!"},
    {7, "!! Network Error !!"},
    {8, "!! AddressInUse Error !!"},
    {9, "!! SocketAddressNotAvailable Error !!"},
    {10, "!! UnsupportedSocketOperation Error !!"},
    {11, "!! UnfinishedSocketOperation Error !!"},
    {12, "!! ProxyAuthenticationRequired Error !!"},
    {13, "!! SslHandshakeFailed Error !!"},
    {14, "!! ProxyConnectionRefused Error !!"},
    {15, "!! ProxyConnectionClosed Error !!"},
    {16, "!! ProxyConnectionTimeout Error !!"},
    {17, "!! ProxyNotFound Error !!"},
    {18, "!! ProxyProtocol Error !!"},
    {19, "!! Operation Error !!"},
    {20, "!! SslInternal Error !!"},
    {21, "!! SslInvalidUserData Error !!"},
    {22, "!! Temporary Error !!"}
};

static std::string getMyIp()
{
    foreach(const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces())
    {
        QNetworkInterface::InterfaceFlags flags = netInterface.flags();
        if((bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)) {
            foreach (const QNetworkAddressEntry &address, netInterface.addressEntries())
            {
                if(address.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    return address.ip().toString().toStdString();
                }
            }
        }
    }
    return "127.0.0.1";
}

MainWindow::MainWindow(const QString hostAddress, int portVal, int audioPort)
    : _tcpClient(hostAddress, portVal)
{
    this->setFixedSize({WIDTH, HEIGHT});
    setWindowTitle("Babel");
    this->setStyleSheet(
        "background-image:url("
        BACKGROUND_PATH
        "); background-position: center;");

    _infos.port = std::to_string(portVal);
    _infos.audioPort = audioPort;
    _infos.myIp = getMyIp();
    _pages = std::make_unique<PageManager>(this, _infos);

    initConnections();
    signalReceivedLoader();
    this->setCentralWidget(_pages.get());
}

MainWindow::~MainWindow()
{
    std::cout << "MainWindow détruit" << std::endl;
}

void MainWindow::signalReceivedLoader()
{
    _signalPageMap[EloginSuccessful] = [&](ClientInfos_t info){
        emit MainWindow::validSignInResponse(info);};
    _signalPageMap[EloginFailed] = [&](ClientInfos_t info){
        emit MainWindow::wrongSignInResponse(info);};
    _signalPageMap[EregisterSuccessful] = [&](ClientInfos_t info){
        emit MainWindow::validRegisterResponse(info);};
    _signalPageMap[EregisterFailed] = [&](ClientInfos_t info){
        emit MainWindow::wrongRegisterResponse(info);};
    _signalPageMap[EincomingCall] = [&](ClientInfos_t info){
        emit MainWindow::incomingCall(info);};
    _signalPageMap[EinvitationReceive] = [&](ClientInfos_t info){
        emit MainWindow::invitationContactReceived(info);};
    _signalPageMap[EcontactExist] = [&](ClientInfos_t info){
        emit MainWindow::contactAddSuccess(info);};
    _signalPageMap[EcontactAddFailed] = [&](ClientInfos_t info){
        emit MainWindow::contactAddFailed(info);};
    _signalPageMap[EcallWasRefused] = [&](ClientInfos_t info){
        emit MainWindow::callRefused(info);};
    _signalPageMap[EcontactList] = [&](ClientInfos_t info){
        emit MainWindow::contactList(info);};
}

void MainWindow::receivedSomething(QByteArray msg)
{
    packet_t *package = reinterpret_cast<packet_t *>(msg.data());

    if (package->magic != MAGIC) {
        std::cout << "** received a packet with wrong MAGIC number **" << std::endl;
        return;
    }
    std::cout << "------------- J'ai reçu ---------------" << std::endl;
    std::cout << *package;
    std::cout << "---------------------------------------" << std::endl;

    if (package->code == EloginSuccessful || package->code == EregisterSuccessful)
        _infos.username = package->data;
    _infos.currentData = package->data;

    if (_signalPageMap.find((receivedSignal_e)package->code) == _signalPageMap.end()) {
        std::cout << "got an unknown code : " << package->code << std::endl;
    } else {
        std::cout << "got a code : " << package->code << std::endl;
        _signalPageMap.at((receivedSignal_e)package->code)(_infos);
    }
}

void MainWindow::changeCurrentPage(pageNames name, ClientInfos_t info)
{
    std::cout << "page change request" << std::endl;
    _pages->setCurrentPage(name, info);
}

void MainWindow::checkSignal(ClientInfos_t infos, signal_e e)
{
    char *buffTemp = CommandsFactory::callCommand(infos, e);
    if (!buffTemp)
        return;
    QByteArray QBta = QByteArray::fromRawData(buffTemp, sizeof(packet_t));

    if (e == Elogin || e == Eregister) {
        _infos.username = infos.username;
        _infos.password = infos.password;
    }

    _tcpClient.send(QBta);
}

void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    std::cout << errSockMap[err] << std::endl;
}

void MainWindow::initConnections(void)
{
    QObject::connect(
        _pages->getPage(LOGIN), SIGNAL(checkCommand(ClientInfos_t, signal_e)),
        this, SLOT(checkSignal(ClientInfos_t, signal_e)));
    QObject::connect(
        _pages->getPage(LOGIN), SIGNAL(changePage(pageNames, ClientInfos_t)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos_t)));
    QObject::connect(
        _pages->getPage(REGISTER), SIGNAL(checkCommand(ClientInfos_t, signal_e)),
        this, SLOT(checkSignal(ClientInfos_t, signal_e)));
    QObject::connect(
        _pages->getPage(REGISTER), SIGNAL(changePage(pageNames, ClientInfos_t)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos_t)));
    QObject::connect(
        _pages->getPage(CALL), SIGNAL(checkCommand(ClientInfos_t, signal_e)),
        this, SLOT(checkSignal(ClientInfos_t, signal_e)));
    QObject::connect(
        _pages->getPage(CALL), SIGNAL(changePage(pageNames, ClientInfos_t)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos_t)));
    QObject::connect(
        _pages->getPage(CONTACTS), SIGNAL(changePage(pageNames, ClientInfos_t)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos_t)));
    QObject::connect(
        _pages->getPage(CONTACTS), SIGNAL(checkCommand(ClientInfos_t, signal_e)),
        this, SLOT(checkSignal(ClientInfos_t, signal_e)));
    QObject::connect(
        &_tcpClient, &Client::Network::TcpClient::dataAvailable,
        this, &MainWindow::receivedSomething);
    QObject::connect(
        _tcpClient.getSocket(), SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(gotError(QAbstractSocket::SocketError)));
}

#include "moc_MainWindow.cpp"
