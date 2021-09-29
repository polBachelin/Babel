/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef CLASS_HPP_
#define CLASS_HPP_


#endif /* !CLASS_HPP_ */

#include "TcpConnection.hpp"

class TcpServer {
    public:
        void start_accept();
        TcpServer(asio::io_context &);
        ~TcpServer();
        void handle_accept(TcpConnection::pointer new_connection, const asio::error_code& error);
    private:
        asio::io_context &_io;
        asio::ip::tcp::acceptor _acceptor;
        std::deque<TcpConnection::pointer> _clients;
};
