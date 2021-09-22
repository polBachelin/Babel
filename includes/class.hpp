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
#include <ctime>
#include <memory>

class printer {
    public:
        printer(asio::io_context &io)
            :_timer(io, asio::chrono::seconds(1)), _count(0)
            {
                _timer.async_wait(std::bind(&printer::print, this));
            }
        ~printer()
            {
                std::cout << "Final is " << _count << std::endl;
            }
        void print()
            {
                if (_count < 5) {
                    std::cout << _count << std::endl;
                    ++_count;
                    _timer.expires_at(_timer.expiry() + asio::chrono::seconds(1));
                    _timer.async_wait(std::bind(&printer::print, this));
                }
            }
    private:
        asio::steady_timer _timer;
        int _count;
};

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
    public:
        tcp_connection(asio::io_context& io_context) : _socket(io_context) {}
        ~tcp_connection() {}
        typedef std::shared_ptr<tcp_connection> pointer;
        static pointer create(asio::io_context& io_context);
        asio::ip::tcp::socket &socket();
        void start();
        void handle_write(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
    private:
        asio::ip::tcp::socket _socket;
        std::string _message;
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
};
