/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_client
*/

#include "AsioTcpConnection.hpp"

AsioTcpConnection::AsioTcpConnection(asio::io_context& io_context, std::deque<pointer_t> &list) : _socket(io_context), _um(_socket), _list(list)
{
    _packet.code = 84;
    _packet.magic = 0;
    _packet.data_size = 0;
}

AsioTcpConnection::~AsioTcpConnection()
{
    _socket.close();
}

void AsioTcpConnection::start()
{
    // asio::async_write(_socket, asio::buffer(_message),
    //     std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    auto handler = std::bind(&AsioTcpConnection::HandleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

void AsioTcpConnection::interpret()
{
    auto tmp = Commands::redirect(_um, _packet, _list);
    if (tmp && tmp->code != 666) {
        auto handler = std::bind(&AsioTcpConnection::handleWrite, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        asio::async_write(_socket, asio::buffer(tmp, sizeof(packet_t)), handler);
    }
    if (tmp)
        delete tmp;
}

pointer_t AsioTcpConnection::create(asio::io_context& io_context, std::deque<pointer_t> &list)
{
    return pointer_t(new AsioTcpConnection(io_context, list));
}

asio::ip::tcp::socket &AsioTcpConnection::socket()
{
    return _socket;
}

void AsioTcpConnection::handleWrite(const asio::error_code &e, size_t size)
{
    if (e || size == 0)
        throw e;
}

void AsioTcpConnection::HandleReadHeader(const asio::error_code &e, std::size_t size)
{
    if (size > 0 && !e) {
        _packet = *(packet_t *)_buffer;
        auto handler = std::bind(&AsioTcpConnection::HandleReadData, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(_buffer, _packet.data_size), handler);
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
    _socket.async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

void AsioTcpConnection::HandleReadData(const asio::error_code &e, std::size_t size)
{
    if (size > 0 && !e) {
        strcpy(_packet.data, _buffer);
        std::cout << "Data : " << _packet.data << std::endl;
        interpret();
        auto handler = std::bind(&AsioTcpConnection::HandleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
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
    _socket.async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

UserManager &AsioTcpConnection::getUsermanager()
{
    return _um;
}
