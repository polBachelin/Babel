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

MainWindow::MainWindow(const QString hostAddress, int portVal)
    : _pages(this), _tcpClient(hostAddress, portVal)
{
    this->setFixedSize({WIDTH, HEIGHT});
    setWindowTitle("Babel");
    this->setCentralWidget(&_pages);
    this->setStyleSheet(
        "background-image:url("
        BACKGROUND_PATH
        "); background-position: center;");

    _infos.port = std::to_string(portVal);

    initConnections();
    signalReceivedLoader();

    foreach (const QNetworkInterface &netInterface, QNetworkInterface::allInterfaces()) {
        QNetworkInterface::InterfaceFlags flags = netInterface.flags();
        if( (bool)(flags & QNetworkInterface::IsRunning) && !(bool)(flags & QNetworkInterface::IsLoopBack)){
            foreach (const QNetworkAddressEntry &address, netInterface.addressEntries()) {
                if(address.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    _infos.ip = address.ip().toString().toStdString();
                    return;
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    std::cout << "MainWindow détruit" << std::endl;
}

void MainWindow::signalReceivedLoader()
{
    _signalPageMap[100] = [&](ClientInfos info){
        emit MainWindow::validSignInResponse(info);};
    _signalPageMap[200] = [&](ClientInfos info){
        emit MainWindow::wrongSignInResponse(info);};
    _signalPageMap[101] = [&](ClientInfos info){
        emit MainWindow::validRegisterResponse(info);};
    _signalPageMap[201] = [&](ClientInfos info){
        emit MainWindow::wrongRegisterResponse(info);};
    _signalPageMap[303] = [&](ClientInfos info){
        emit MainWindow::incomingCall(info);};
    _signalPageMap[12] = [&](ClientInfos info){
        emit MainWindow::invitationContactReceived(info);};
    _signalPageMap[102] = [&](ClientInfos info){
        emit MainWindow::contactAddSuccess(info);};
    _signalPageMap[202] = [&](ClientInfos info){
        emit MainWindow::contactAddFailed(info);};
    _signalPageMap[203] = [&](ClientInfos info){
        emit MainWindow::callRefused(info);};
    _signalPageMap[4] = [&](ClientInfos info){
        emit MainWindow::contactList(info);};
}

void MainWindow::receivedSomething(QByteArray msg)
{
    packet_t *package = reinterpret_cast<packet_t *>(msg.data());

    if (package->magic != MAGIC) {
        std::cout << "** received a packet with wrong MAGIC number **" << std::endl;
        return;
    }
    std::cout << "J'ai reçu" << std::endl;
    std::cout << "Magic = " << package->magic << std::endl;
    std::cout << "Code  = " << package->code << std::endl;
    std::cout << "size  = " << package->data_size << std::endl;
    std::cout << "data  = " << package->data << std::endl;

    // package->code = (package->code == 10 ? 123456 : package->code);

    std::string test(package->data);
    _infos.username = test;
    _infos.currentData = package->data;

    bool isCoded = false;
    for (auto &it : _signalPageMap){
        std::cout << "test the code : " << it.first << std::endl;
        if (it.first == package->code) {
            std::cout << "got a code : " << package->code << std::endl;
            isCoded = true;
            _signalPageMap.at(package->code)(_infos);
        }
    }
    if (!isCoded)
        std::cout << "got an unknown code : " << package->code << std::endl;
    // if (_signalPageMap.find(package->code) == _signalPageMap.end()) {
    //     std::cout << "got an unknown code : " << package->code << std::endl;
    // } else {
    //     std::cout << "got a code : " << package->code << std::endl;
    //     _signalPageMap.at(package->code)(_infos);
    // }
}

void MainWindow::changeCurrentPage(pageNames name, ClientInfos info)
{
    std::cout << "page change request" << std::endl;
    _pages.setCurrentPage(name, info);
}

void MainWindow::checkSignal(ClientInfos infos, signal_e e)
{
    char *buffTemp = CommandsFactory::callCommand(infos, e);
    QByteArray QBta = QByteArray::fromRawData(buffTemp, sizeof(packet_t));

    if (e == Elogin || e == Eregister) {
        _infos.username = infos.username;
        _infos.password = infos.password;
    }
    std::cout << "US " << infos.ip << " send infos: " << std::endl;

    std::cout << infos.ip << std::endl;
    std::cout << infos.userToCall << std::endl;
    std::cout << infos.currentData << std::endl;
    _tcpClient.send(QBta);
}

void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    std::cout << errSockMap[err] << std::endl;
}

void MainWindow::onStartCallConnection(ClientInfos info)
{

}

void MainWindow::initConnections(void)
{
    QObject::connect(
        _pages.getPage(LOGIN), SIGNAL(checkCommand(ClientInfos, signal_e)),
        this, SLOT(checkSignal(ClientInfos, signal_e)));
    QObject::connect(
        _pages.getPage(LOGIN), SIGNAL(changePage(pageNames, ClientInfos)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos)));
    QObject::connect(
        _pages.getPage(REGISTER), SIGNAL(checkCommand(ClientInfos, signal_e)),
        this, SLOT(checkSignal(ClientInfos, signal_e)));
    QObject::connect(
        _pages.getPage(REGISTER), SIGNAL(changePage(pageNames, ClientInfos)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos)));
    QObject::connect(
        _pages.getPage(CALL), SIGNAL(checkCommand(ClientInfos, signal_e)),
        this, SLOT(checkSignal(ClientInfos, signal_e)));
    QObject::connect(
        _pages.getPage(CALL), SIGNAL(changePage(pageNames, ClientInfos)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos)));
    QObject::connect(
        _pages.getPage(CONTACTS), SIGNAL(changePage(pageNames, ClientInfos)),
        this, SLOT(changeCurrentPage(pageNames, ClientInfos)));
    QObject::connect(
        _pages.getPage(CONTACTS), SIGNAL(checkCommand(ClientInfos, signal_e)),
        this, SLOT(checkSignal(ClientInfos, signal_e)));
    QObject::connect(
        &_tcpClient, &Client::Network::TcpClient::dataAvailable,
        this, &MainWindow::receivedSomething);
    QObject::connect(
        _tcpClient.getSocket(), SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(gotError(QAbstractSocket::SocketError)));
}

#include "moc_MainWindow.cpp"
