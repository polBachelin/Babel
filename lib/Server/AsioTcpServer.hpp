/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef ASIOTCPSERVER_HPP_
#define ASIOTCPSERVER_HPP_

#include <thread>
#include <mutex>
#include "AsioTcpConnection.hpp"
#include "ITcpServer.hpp"

class AsioTcpServer : public ITcpServer {
    public:
        AsioTcpServer();
        ~AsioTcpServer();
        void acceptConnection() override;
        void initServer(int port) override;
        void run() override;
        void listen();
        void printLocalAdress();
        void handleAccept(std::shared_ptr<AsioTcpConnection> new_connection, const asio::error_code& error);
        std::deque<std::shared_ptr<ClientManager>> &getClientList();

    private:
        std::shared_ptr<asio::io_context> _io;
        int _port = 0;
        std::unique_ptr<asio::ip::tcp::acceptor> _acceptor;
        std::deque<std::shared_ptr<ClientManager>> _clients;
        std::unique_ptr<std::thread> _runThread;
        std::mutex _mtx;
};

#endif /* !ASIOTCPSERVER_HPP_ */