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

    std::cout << "receive_header : " << _receive  << " size " << size << std::endl;
    if (size > 0) {
        std::cout << "message received : " << std::endl;
        tmp = (packet_t *)_receive;
        auto handler = std::bind(&TcpConnection::handle_read_data, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(_packet, tmp->data_size), handler);
        return;
    } else if (e)
        std::cout << "An error occur " << e.message() << std::endl;
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_packet, 3 * sizeof(int)), handler);
}

void TcpConnection::handle_read_data(const asio::error_code &e, std::size_t size)
{
    packet_t *tmp;

    std::cout << "receive_data : " << _receive  << " size " << size << std::endl;
    if (size > 0) {
        std::cout << "message received : " << std::endl;
        tmp = (packet_t *)_receive;
        interpret(tmp);
        auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket.async_read_some(asio::buffer(_packet, tmp->data_size), handler);
        return;
    } else if (e)
        std::cout << "An error occur " << e.message() << std::endl;
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_packet, 3 * sizeof(int)), handler);
}

TcpConnection::TcpConnection(asio::io_context& io_context) : _socket(io_context)
{
}

void TcpConnection::start()
{
    _message = make_daytime_string();
    // asio::async_write(_socket, asio::buffer(_message),
    //     std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    auto handler = std::bind(&TcpConnection::handle_read_header, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket.async_read_some(asio::buffer(_packet, sizeof(int) * 3), handler);
}
