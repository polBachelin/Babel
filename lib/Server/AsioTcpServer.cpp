/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_server
*/

#include "AsioTcpServer.hpp"

extern "C"
{
    std::shared_ptr<ITcpServer> entryPoint()
    {
        return std::make_shared<AsioTcpServer>();
    }
}

AsioTcpServer::AsioTcpServer()
{
}

AsioTcpServer::~AsioTcpServer()
{
}

void AsioTcpServer::startAccept()
{
    AsioTcpConnection::pointer new_connection = AsioTcpConnection::create(*_io.get());

    _acceptor->async_accept(new_connection->socket(),
        std::bind(&AsioTcpServer::handleAccept, this, new_connection, std::placeholders::_1));
    _clients.push_back(new_connection);
    _io->run();
}

void AsioTcpServer::initServer(int port)
{
    _io = std::make_shared<asio::io_context>();
    _port = port;
    _acceptor = std::make_unique<asio::ip::tcp::acceptor>(*_io.get(), asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
    _acceptor->set_option(asio::ip::tcp::acceptor::reuse_address(true));
}

void AsioTcpServer::handleAccept(AsioTcpConnection::pointer new_connection, const asio::error_code& error)
{
    if (!error) {
        new_connection->start();
    }
    AsioTcpServer::startAccept();
}
