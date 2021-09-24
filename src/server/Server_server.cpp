/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_server
*/

#include "class.hpp"

void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(_io);

    _acceptor.async_accept(new_connection->socket(),
        std::bind(&tcp_server::handle_accept, this, new_connection, std::placeholders::_1));
    _clients.push_back(new_connection);
}

tcp_server::tcp_server(asio::io_context &io) : _io(io), _acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 5000))
{
    _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    start_accept();
}

tcp_server::~tcp_server()
{

}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const asio::error_code& error)
{
    if (!error) {
            new_connection->start();
    }
    tcp_server::start_accept();
}
