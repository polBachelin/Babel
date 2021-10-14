/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Server_client
*/

#include "AsioTcpConnection.hpp"

AsioTcpConnection::AsioTcpConnection(asio::io_context& io_context, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
    : _list(list)
{
    _socket = std::make_shared<asio::ip::tcp::socket>(io_context);
    _buffer.fill(0);
    _packet.code = 84;
    _packet.magic = 0;
    _packet.data_size = 0;
    _packet.data.fill(0);
}

AsioTcpConnection::AsioTcpConnection(const AsioTcpConnection &ref)
    : std::enable_shared_from_this<AsioTcpConnection>(), _packet(ref._packet), _list(ref._list)
{
    _socket = ref._socket;
}

AsioTcpConnection::~AsioTcpConnection()
{
    _socket->close();
}

void AsioTcpConnection::start()
{
    // asio::async_write(_socket, asio::buffer(_message),
    //     std::bind(&tcp_connection::handle_write, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

void AsioTcpConnection::interpret()
{
    pck_list *res = Commands::redirect(std::make_shared<AsioTcpConnection>(*this), _packet, _list);
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

std::shared_ptr<AAsioTcpConnection> AsioTcpConnection::create(asio::io_context& io_context, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    return std::make_shared<AsioTcpConnection>(io_context, list);
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
        _packet = *(packet_t *)_buffer.data();
        auto handler = std::bind(&AsioTcpConnection::handleReadData, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket->async_read_some(asio::buffer(_buffer, _packet.data_size), handler);
        return;
    } else if (e) {
        if (e == asio::error::eof) {
            _socket->close();
            delete this;
            return;
        }
        std::cout << "An error occur " << e.message() << std::endl;
    }
    _buffer.fill(0);
    auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

void AsioTcpConnection::handleReadData(const asio::error_code &e, std::size_t size)
{
    if (size > 0 && !e) {
        _packet.data = _buffer;
        interpret();
        _buffer.fill(0);
        auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
        _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
        return;
    } else if (e) {
        if (e == asio::error::eof) {
            _socket->close();
            delete this;
            return;
        }
        std::cout << "An error occur data :" << e.message() << std::endl;
    }
    _buffer.fill(0);
    auto handler = std::bind(&AsioTcpConnection::handleReadHeader, shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    _socket->async_read_some(asio::buffer(_buffer, sizeof(packet_info_t)), handler);
}

const std::shared_ptr<asio::ip::tcp::socket> AsioTcpConnection::getSocket() const
{
    return _socket;
}

const std::string &AsioTcpConnection::getUserName() const
{
    return _um.GetName();
}

const std::string &AsioTcpConnection::getUserContactList() const
{
    return _um.GetContactManager().getContactList(_um.GetName());
}

int AsioTcpConnection::Login(const std::string &name, const std::string &passwd)
{
    return _um.login(name, passwd);
}

int AsioTcpConnection::NewUser(const std::string &name, const std::string &passwd)
{
    return _um.new_user(name, passwd);
}

void AsioTcpConnection::addContact(const std::string &new_c, const std::string &your_name)
{
    return _um.GetContactManager().addContact(new_c, your_name);
}
