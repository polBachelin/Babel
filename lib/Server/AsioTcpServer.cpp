/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_server
*/

#include "AsioTcpServer.hpp"

// extern "C"
// {
//     std::shared_ptr<ITcpServer> entryPoint()
//     {
//         return std::make_shared<AsioTcpServer>();
//     }
//

AsioTcpServer::AsioTcpServer()
{
}

AsioTcpServer::~AsioTcpServer()
{
    _io->stop();
}

void AsioTcpServer::run()
{
    if (_io)
        _io->run();
}

void AsioTcpServer::acceptConnection()
{
    std::shared_ptr<AsioTcpConnection> new_connection = std::make_shared<AsioTcpConnection>(*_io.get(), _clients);

    _clients.push_back(new_connection->getClientManager());
    _acceptor->async_accept(*new_connection->getSocket(),
        std::bind(&AsioTcpServer::handleAccept, this, new_connection, std::placeholders::_1));
}

void AsioTcpServer::printLocalAdress()
{
    try {
        asio::io_service netService;
        asio::ip::udp::resolver resolver(netService);
        asio::ip::udp::resolver::query query(asio::ip::udp::v4(), "google.com", "");
        asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);
        asio::ip::udp::endpoint ep = *endpoints;
        asio::ip::udp::socket socket(netService);
        socket.connect(ep);
        asio::ip::address addr = socket.local_endpoint().address();
        std::cout << "Server IP : " << addr.to_string() << std::endl;
    } catch (std::exception& e){
        std::cerr << "Could not find our IP adress : " << e.what() << std::endl;
    }
}

void AsioTcpServer::initServer(int port)
{
    _io = std::make_shared<asio::io_context>();
    _port = port;
    _acceptor = std::make_unique<asio::ip::tcp::acceptor>(*_io.get(), asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
    _acceptor->set_option(asio::ip::tcp::acceptor::reuse_address(true));
    printLocalAdress();
}

void AsioTcpServer::handleAccept(std::shared_ptr<AsioTcpConnection> new_connection, const asio::error_code& error)
{
    if (!error) {
        new_connection->start();
    }
    acceptConnection();
    if (error)
        std::cerr << error.message() << std::endl;
}

std::deque<std::shared_ptr<ClientManager>> &AsioTcpServer::getClientList()
{
    return _clients;
}
