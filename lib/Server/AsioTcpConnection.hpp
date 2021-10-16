/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef ASIOTCPCONNECTION_HPP_
#define ASIOTCPCONNECTION_HPP_

#include "CommandsManager.hpp"
#include "ITcpConnection.hpp"

class AsioTcpConnection : public std::enable_shared_from_this<AsioTcpConnection>, public ITcpConnection {
    public:
        AsioTcpConnection(asio::io_context& io_context, std::deque<std::shared_ptr<ClientManager>> &);
        AsioTcpConnection(const AsioTcpConnection &);
        ~AsioTcpConnection();        
        void start() override;

        void handleWrite(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
        void handleReadHeader(const asio::error_code &, std::size_t);
        void handleReadData(const asio::error_code &, std::size_t);

        std::shared_ptr<asio::ip::tcp::socket> getSocket() const;
        std::shared_ptr<ClientManager> getClientManager() const;
        void interpret();

        bool isAlive() const;
    private:
        std::array<char, 2048> _buffer;
        std::shared_ptr<asio::ip::tcp::socket> _socket;
        std::shared_ptr<ClientManager> _clientManager;
        std::deque<std::shared_ptr<ClientManager>> &_clients;
        bool _isAlive;
};

#endif /* !ASIOTCPCONNECTION_HPP_ */