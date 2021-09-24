/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_client
*/

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

void tcp_connection::interpret(packet_t *pack)
{

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
}

void tcp_connection::handle_read_header(const asio::error_code &e, std::size_t size)
{
    packet_t *tmp;

    if (size > 0) {
        std::cout << "message received : " << _receive << std::endl;
        tmp = (packet_t *)_receive;
        auto handler = std::bind(&tcp_connection::handle_read_data, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(_receive, tmp->data_size), handler);
        return;
    } else if (e)
        std::cout << "An error occur " << e.message() << std::endl;
    auto handler = std::bind(&tcp_connection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_receive, sizeof(packet_t)), handler);
}

void tcp_connection::handle_read_data(const asio::error_code &e, std::size_t size)
{
    packet_t *tmp;

    if (size > 0) {
        std::cout << "message received : " << _receive << std::endl;
        tmp = (packet_t *)_receive;
        interpret(tmp);
        auto handler = std::bind(&tcp_connection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(_receive, tmp->data_size), handler);
        return;
    } else if (e)
        std::cout << "An error occur " << e.message() << std::endl;
    auto handler = std::bind(&tcp_connection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_receive, sizeof(packet_t)), handler);
}

tcp_connection::tcp_connection(asio::io_context& io_context) : _socket(io_context)
{
}

void tcp_connection::start()
{
    _message = make_daytime_string();
    // asio::async_write(_socket, asio::buffer(_message),
    //     std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    auto handler = std::bind(&tcp_connection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_receive, sizeof(packet_t)), handler);
}
