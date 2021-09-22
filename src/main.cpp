/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include "class.hpp"

std::string make_daytime_string()
{
    std::time_t now = std::time(NULL);

    return std::ctime(&now);
}

tcp_connection::pointer tcp_connection::create(asio::io_context& io_context)
{
    return pointer(new tcp_connection(io_context));
}

asio::ip::tcp::socket &tcp_connection::socket()
{
    return _socket;
}

void tcp_connection::handle_write(const asio::error_code &e, size_t size)
{
    std::cout << "salut" << std::endl;
}

void tcp_connection::start()
{
    _message = make_daytime_string();
    asio::async_write(_socket, asio::buffer(_message),
        std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));

}

void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(_io);

    _acceptor.async_accept(new_connection->socket(),
        std::bind(&tcp_server::handle_accept, this, new_connection, std::placeholders::_1));
}

tcp_server::tcp_server(asio::io_context &io) : _io(io), _acceptor(io, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 5000))
{
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

int main(int ac, char **av)
{
    try {
        asio::io_context io;
        tcp_server server(io);
        io.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}