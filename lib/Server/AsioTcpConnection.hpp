/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef CLASS_HPP_
#define CLASS_HPP_

#endif /* !CLASS_HPP_ */

#include "Commands.hpp"

class AsioTcpConnection : public std::enable_shared_from_this<AsioTcpConnection> {
    public:
        AsioTcpConnection(asio::io_context& io_context);
        ~AsioTcpConnection();
        typedef std::shared_ptr<AsioTcpConnection> pointer;
        static pointer create(asio::io_context& io_context);
        asio::ip::tcp::socket &socket();
        void start();
        void handleWrite(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
        void HandleReadHeader(const asio::error_code &, std::size_t);
        void HandleReadData(const asio::error_code &, std::size_t);
        void interpret();
    private:
        asio::ip::tcp::socket _socket;
        std::string _message;
        packet_t _packet;
        char test[2048] = {0};
        UserManager _um;
};
