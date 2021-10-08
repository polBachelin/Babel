/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef ASIOTCPCONNECTION_HPP_
#define ASIOTCPCONNECTION_HPP_

#include "Commands.hpp"

class AsioTcpConnection : public std::enable_shared_from_this<AsioTcpConnection>, public AAsioTcpConnection {
    public:
        AsioTcpConnection(asio::io_context& io_context, std::deque<pointer_t> &);
        ~AsioTcpConnection();
        static pointer_t create(asio::io_context& io_context, std::deque<pointer_t> &);
        asio::ip::tcp::socket &socket();
        void start();
        void handleWrite(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
        void HandleReadHeader(const asio::error_code &, std::size_t);
        void HandleReadData(const asio::error_code &, std::size_t);
        void interpret();
        UserManager &getUsermanager();
    private:
        asio::ip::tcp::socket _socket;
        std::string _message;
        packet_t _packet;
        char _buffer[2048] = {0};
        UserManager _um;
        std::deque<pointer_t> &_list;
};

#endif /* !ASIOTCPCONNECTION_HPP_ */