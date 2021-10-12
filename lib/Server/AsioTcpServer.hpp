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
        void startAccept() override;
        void reAccept();
        void initServer(int port) override;
        void printLocalAdress();
        void handleAccept(pointer_t new_connection, const asio::error_code& error);
        std::deque<pointer_t> &getClientList();
    private:
        std::shared_ptr<asio::io_context> _io;
        int _port = 0;
        std::unique_ptr<asio::ip::tcp::acceptor> _acceptor;
        std::deque<pointer_t> _clients;

};

#endif /* !ASIOTCPSERVER_HPP_ */