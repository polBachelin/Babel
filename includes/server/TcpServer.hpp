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
#include "TcpConnection.hpp"
#include "Database.hpp"

class TcpServer : public ITcpServer {
    public:
        void startAccept() override;
        void initServer(int port) override;
        TcpServer(asio::io_context &);
        ~TcpServer();
        void handleAccept(TcpConnection::pointer new_connection, const asio::error_code& error);
    private:
        asio::io_context &_io;
        int _port;
        asio::ip::tcp::acceptor _acceptor;
        std::deque<TcpConnection::pointer> _clients;
        Database _db;

};
