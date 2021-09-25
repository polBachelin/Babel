/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_server
*/

#include "TcpServer.hpp"

void TcpServer::start_accept()
{
    TcpConnection::pointer new_connection = TcpConnection::create(_io);

    _acceptor.async_accept(new_connection->socket(),
        std::bind(&TcpServer::handle_accept, this, new_connection, std::placeholders::_1));
    _clients.push_back(new_connection);
}

TcpServer::TcpServer(asio::io_context &io) : _io(io), _acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 5000))
{
    _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    start_accept();
}

TcpServer::~TcpServer()
{

}

void TcpServer::handle_accept(TcpConnection::pointer new_connection, const asio::error_code& error)
{
    if (!error) {
            new_connection->start();
    }
    TcpServer::start_accept();
}
