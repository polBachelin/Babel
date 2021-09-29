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

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
    public:
        TcpConnection(asio::io_context& io_context);
        ~TcpConnection() {}
        typedef std::shared_ptr<TcpConnection> pointer;
        static pointer create(asio::io_context& io_context);
        asio::ip::tcp::socket &socket();
        void start();
        void handle_write(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
        void handle_read_header(const asio::error_code &, std::size_t);
        void handle_read_data(const asio::error_code &, std::size_t);
        void interpret();
    private:
        asio::ip::tcp::socket _socket;
        std::string _message;
        void *_receive;
        packet_t _packet;
        char test[2048] = {0};
};
