/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef CLASS_HPP_
#define CLASS_HPP_

#endif /* !CLASS_HPP_ */

#include "ITcpConnection.hpp"

class TcpConnection : public ITcpConnection, public std::enable_shared_from_this<TcpConnection> {
    public:
        TcpConnection(asio::io_context& io_context);
        ~TcpConnection() {}
        typedef std::shared_ptr<TcpConnection> pointer;
        static pointer create(asio::io_context& io_context);
        asio::ip::tcp::socket &socket();
        void start() override;
        void handle_write(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
        void HandleReadHeader(const asio::error_code &, std::size_t);
        void HandleReadData(const asio::error_code &, std::size_t);
        void interpret() override;
    private:
        asio::ip::tcp::socket _socket;
        std::string _message;
        void *_receive;
        packet_t _packet;
        char test[2048] = {0};
};
