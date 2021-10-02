/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_client
*/

#include "AsioTcpConnection.hpp"

void AsioTcpConnection::interpret()
{
    Commands::redirect(_socket, _um, _packet);
}

AsioTcpConnection::pointer AsioTcpConnection::create(asio::io_context& io_context)
{
    return pointer(new AsioTcpConnection(io_context));
}

asio::ip::tcp::socket &AsioTcpConnection::socket()
{
    return _socket;
}

void AsioTcpConnection::handle_write(const asio::error_code &e, size_t size)
{
}

void AsioTcpConnection::HandleReadHeader(const asio::error_code &e, std::size_t size)
{
    packet_t *tmp;

    if (size > 0 && !e) {
        _packet = *(packet_t *)test;
        auto handler = std::bind(&AsioTcpConnection::HandleReadData, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(test, _packet.data_size), handler);
        return;
    } else if (e) {
        if (e == asio::error::eof) {
            _socket.close();
            delete this;
            return;
        }
        std::cout << "An error occur " << e.message() << std::endl;
    }
    auto handler = std::bind(&AsioTcpConnection::HandleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}

void AsioTcpConnection::HandleReadData(const asio::error_code &e, std::size_t size)
{
    packet_t *tmp;

    if (size > 0 && !e) {
        strcpy(_packet.data, test);
        std::cout << "Data : " << _packet.data << std::endl;
        interpret();
        auto handler = std::bind(&AsioTcpConnection::HandleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
        return;
    } else if (e) {
        if (e == asio::error::eof) {
            _socket.close();
            delete this;
            return;
        }
        std::cout << "An error occur data :" << e.message() << std::endl;
    }
    auto handler = std::bind(&AsioTcpConnection::HandleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}

AsioTcpConnection::AsioTcpConnection(asio::io_context& io_context) : _socket(io_context), _um()
{
    _packet.code = 84;
    _packet.magic = 0;
    _packet.data_size = 0;
}

void AsioTcpConnection::start()
{
    // asio::async_write(_socket, asio::buffer(_message),
    //     std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    auto handler = std::bind(&AsioTcpConnection::HandleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(test, sizeof(packet_info_t)), handler);
}
