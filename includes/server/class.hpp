/*
** EPITECH PROJECT, 2021
** babel
** File description:
** class
*/

#ifndef CLASS_HPP_
#define CLASS_HPP_


#endif /* !CLASS_HPP_ */

#include <iostream>
#include <asio.hpp>
#include <array>
#include <deque>
#include <ctime>
#include <memory>

#define MAGIC 12324342212

typedef struct packet {
    int magic;
    int code;
    int data_size;
    void *data;
} packet_t;

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
    public:
        tcp_connection(asio::io_context& io_context);
        ~tcp_connection() {}
        typedef std::shared_ptr<tcp_connection> pointer;
        static pointer create(asio::io_context& io_context);
        asio::ip::tcp::socket &socket();
        void start();
        void handle_write(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
        void handle_read_header(const asio::error_code &, std::size_t);
        void handle_read_data(const asio::error_code &, std::size_t);
        void interpret(packet_t *pack);
    private:
        asio::ip::tcp::socket _socket;
        std::string _message;
        void *_receive;
        packet_t *_packet;
};

class tcp_server {
    public:
        void start_accept();
        tcp_server(asio::io_context &);
        ~tcp_server();
        void handle_accept(tcp_connection::pointer new_connection, const asio::error_code& error);
    private:
        asio::io_context &_io;
        asio::ip::tcp::acceptor _acceptor;
        std::deque<tcp_connection::pointer> _clients;
};
