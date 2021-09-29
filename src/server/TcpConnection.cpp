/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_client
*/

#include "TcpConnection.hpp"

std::string make_daytime_string()
{
    std::time_t now = std::time(NULL);

    return std::ctime(&now);
}

void TcpConnection::interpret()
{
    Commands::redirect(_packet);
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
        _packet = *(packet_t *)test;
        std::cout << "Magic: " << _packet.magic << " Code: " << _packet.code << " data_size: " << _packet.data_size << std::endl; 
        auto handler = std::bind(&TcpConnection::handle_read_data, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(test, _packet.data_size), handler);
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
        strcpy(_packet.data, test);
        std::cout << "Data : " << _packet.data << std::endl;
        interpret();
        auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
        return;
    } else if (e)
        std::cout << "An error occur data :" << e.message() << std::endl;
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}

TcpConnection::TcpConnection(asio::io_context& io_context) : _socket(io_context), _receive(nullptr)
{
    _packet.code = 84;
    _packet.magic = 0;
    _packet.data_size = 0;
}

void TcpConnection::start()
{
    _message = make_daytime_string();
    // asio::async_write(_socket, asio::buffer(_message),
    //     std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}
