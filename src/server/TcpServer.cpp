/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_server
*/

#include "TcpServer.hpp"

void TcpServer::startAccept()
{
    TcpConnection::pointer new_connection = TcpConnection::create(_io);

    _acceptor.async_accept(new_connection->socket(),
        std::bind(&TcpServer::handleAccept, this, new_connection, std::placeholders::_1));
    _clients.push_back(new_connection);
}

void TcpServer::initServer(int port)
{
    _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
}

TcpServer::TcpServer(asio::io_context &io) : _io(io), _port(5000), _acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), _port))
{
    initServer(_port);
    startAccept();
}

TcpServer::~TcpServer()
{

}

void TcpServer::handleAccept(TcpConnection::pointer new_connection, const asio::error_code& error)
{
    if (!error) {
            new_connection->start();
    }
    TcpServer::startAccept();
}
