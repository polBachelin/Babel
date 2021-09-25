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

#include "TcpServer.hpp"

std::string make_daytime_string()
{
    std::time_t now = std::time(NULL);

    return std::ctime(&now);
}

void TcpConnection::interpret(packet_t *pack)
{

}

TcpConnection::pointer TcpConnection::create(asio::io_context& io_context)
{
    return pointer(new TcpConnection(io_context));
}

asio::ip::tcp::socket &TcpConnection::socket()
{
    return _socket;
}

void TcpConnection::handle_write(const asio::error_code &e, size_t size)
{
}

void TcpConnection::handle_read_header(const asio::error_code &e, std::size_t size)
{
    packet_t *tmp;

    if (size > 0) {
        tmp = (packet_t *)test;
        std::cout << "Magic: " << tmp->magic << " Code: " << tmp->code << " data_size: " << tmp->data_size << std::endl; 
        auto handler = std::bind(&TcpConnection::handle_read_data, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(test, tmp->data_size), handler);
        return;
    } else if (e)
        std::cout << "An error occur " << e.message() << std::endl;
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}

void TcpConnection::handle_read_data(const asio::error_code &e, std::size_t size)
{
    packet_t *tmp;

    if (size > 0) {
        //tmp = (packet_t *)test;
        std::cout << "Data : " << test << std::endl;
        interpret(tmp);
        auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(test, tmp->data_size), handler);
        return;
    } else if (e)
        std::cout << "An error occur data :" << e.message() << std::endl;
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}

TcpConnection::TcpConnection(asio::io_context& io_context) : _socket(io_context), _packet(nullptr), _receive(nullptr)
{
}

void TcpConnection::start()
{
    _message = make_daytime_string();
    // asio::async_write(_socket, asio::buffer(_message),
    //     std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}
