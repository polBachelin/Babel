/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef CLASS_HPP_
#define CLASS_HPP_


#endif /* !CLASS_HPP_ */

#include "ITcpServer.hpp"
#include "AsioTcpConnection.hpp"
#include "ContactManager.hpp"

class AsioTcpServer : public ITcpServer {
    public:
        AsioTcpServer() = default;
        ~AsioTcpServer() = default;
        void startAccept() override;
        void reAccept();
        void initServer(int port) override;
        void handleAccept(AsioTcpConnection::pointer new_connection, const asio::error_code& error);
    private:
        std::shared_ptr<asio::io_context> _io;
        int _port = 0;
        std::unique_ptr<asio::ip::tcp::acceptor> _acceptor;
        std::deque<AsioTcpConnection::pointer> _clients;

};
