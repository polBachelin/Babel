/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_client
*/

#include "AsioTcpConnection.hpp"

AsioTcpConnection::AsioTcpConnection(asio::io_context& io_context, std::deque<std::shared_ptr<ClientManager>> &list)
{
    asio::socket_base::receive_buffer_size option_receive_size(sizeof(packet_t));
    asio::socket_base::send_buffer_size option_send_size(sizeof(packet_t));

    _socket = std::make_shared<asio::ip::tcp::socket>(io_context);
    _socket->set_option(option_receive_size);
    _socket->set_option(option_send_size);
    _clientManager = std::make_shared<ClientManager>(_socket);
    _clients = list;
    _buffer.fill(0);
}

AsioTcpConnection::AsioTcpConnection(const AsioTcpConnection &ref)
    : std::enable_shared_from_this<AsioTcpConnection>()
{
    _socket = ref._socket;
}

AsioTcpConnection::~AsioTcpConnection()
{
    _socket->close();
}

std::shared_ptr<asio::ip::tcp::socket> AsioTcpConnection::getSocket() const
{
    return _socket;
}

void AsioTcpConnection::start()
{
    std::cout << "STARTING A NEW TCP CONNECTION\n";

    auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

void AsioTcpConnection::interpret()
{
    pck_list *res = CommandsManager::redirect(_clientManager->getPacket(), _clients, _clientManager);
    if (!res)
        return;
    for (auto it = res->begin(); it != res->end(); it++) {
        std::cout << "interpret " << it->first->is_open() << std::endl;
        auto tmp = it->second;
        if (tmp && tmp->code != 666) {
            std::cout << "---------Sent------------" << std::endl;
            PRINT_PCK((*tmp));
            std::cout << "-------------------------" << std::endl;
            auto handler = std::bind(&AsioTcpConnection::handleWrite, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
            it->first->async_send(asio::buffer(tmp, sizeof(packet_t)), handler);
        }
        if (tmp)
            delete tmp;
    }
}

void AsioTcpConnection::handleWrite(const asio::error_code &e, size_t size)
{
    if (e || size == 0) {
        std::cout << "HandleWrite Error : " << e.message() << std::endl;
        throw e.value();
    }
}

void AsioTcpConnection::handleReadHeader(const asio::error_code &e, std::size_t size)
{
    if (size > 0 && !e) {
        packet_t *tmp = reinterpret_cast<packet_t *>(_buffer.data());
        _clientManager->setPacket(tmp);
        _buffer.fill('\0');
        auto handler = std::bind(&AsioTcpConnection::handleReadData, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket->async_read_some(asio::buffer(_buffer, _clientManager->getPacket().data_size), handler);
        return;
    } else if (e) {
        if (e == asio::error::eof) {
            _socket->close();
            return;
        }
        std::cout << "An error occurred " << e.message() << std::endl;
    }
    _buffer.fill(0);
    auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

void AsioTcpConnection::handleReadData(const asio::error_code &e, std::size_t size)
{
    if (size > 0 && !e) {
        std::cout << "set packet data -- " << _buffer.data() << std::endl;
        _clientManager->setPacketData(_buffer);
        interpret();
        auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
        return;
    } else if (e) {
        if (e == asio::error::eof) {
            _socket->close();
            return;
        }
        std::cout << "An error occur data :" << e.message() << std::endl;
    }
    //_buffer.fill(0);
    auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

std::shared_ptr<ClientManager> AsioTcpConnection::getClientManager() const
{
    return _clientManager;
}