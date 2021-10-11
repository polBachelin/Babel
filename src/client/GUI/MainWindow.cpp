/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** MainWindow
*/

#include "MainWindow.hpp"
#include "APage.hpp"

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

    _signalPageMap[100] = [&](ClientInfos info){
        emit MainWindow::validSignalResponse(info);};
    _signalPageMap[200] = [&](ClientInfos info){
        emit MainWindow::wrongSignalResponse(info);};
    _signalPageMap[101] = [&](ClientInfos info){
        emit MainWindow::validSignalResponse(info);};
    _signalPageMap[201] = [&](ClientInfos info){
        emit MainWindow::wrongSignalResponse(info);};
    // _signalPageMap[012] = [&](ClientInfos info){
    //     emit fct(info);};
    // _signalPageMap[102] = [&](ClientInfos info){
    //     emit fct(info);};
    // _signalPageMap[303] = [&](ClientInfos info){
    //     emit fct(info);};
    // _signalPageMap[203] = [&](ClientInfos info){
    //     emit fct(info);};
    // _signalPageMap[004] = [&](ClientInfos info){
    //     emit fct(info);};

    initConnections();
}

MainWindow::~MainWindow()
{
    std::cout << "MainWindow détruit" << std::endl;
}

void MainWindow::receivedSomething(QByteArray msg)
{
    packet_t *package = reinterpret_cast<packet_t *>(msg.data());

    if (package->magic != MAGIC) {
        std::cout << "** received a packet with wrong MAGIC number **" << std::endl;
        return;
    }
    std::cout << "Magic = " << package->magic << std::endl;
    std::cout << "Code  = " << package->code << std::endl;
    std::cout << "size  = " << package->data_size << std::endl;
    std::cout << "data  = " << package->data << std::endl;

    std::string test(package->data);
    _infos.username = test;
    _signalPageMap.at(package->code)(_infos);
}

void MainWindow::changeCurrentPage(pageNames name, ClientInfos info)
{
    _pages.setCurrentPage(name, info);
}

void MainWindow::checkSignal(ClientInfos infos, signal_e e)
{
    char *buffTemp = CommandsFactory::callCommand(infos, e);
    QByteArray QBta = QByteArray::fromRawData(buffTemp, sizeof(packet_t));

    _infos = infos;
    _tcpClient.send(QBta);
}

void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    std::cout << errSockMap[err] << std::endl;
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
