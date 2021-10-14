/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef ASIOTCPSERVER_HPP_
#define ASIOTCPSERVER_HPP_

#include "AsioTcpConnection.hpp"
#include "ITcpServer.hpp"

class AsioTcpServer : public ITcpServer {
    public:
        AsioTcpServer() = default;
        ~AsioTcpServer() = default;
        void acceptConnection() override;
        void initServer(int port) override;
        void run() override;
        void printLocalAdress();
        void handleAccept(std::shared_ptr<AAsioTcpConnection> new_connection, const asio::error_code& error);
        std::deque<std::shared_ptr<AAsioTcpConnection>> &getClientList();
    private:
        std::shared_ptr<asio::io_context> _io;
        int _port = 0;
        std::unique_ptr<asio::ip::tcp::acceptor> _acceptor;
        std::deque<std::shared_ptr<AAsioTcpConnection>> _clients;

};

#endif /* !ASIOTCPSERVER_HPP_ */