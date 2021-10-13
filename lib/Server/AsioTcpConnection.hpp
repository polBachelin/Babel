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
        AsioTcpConnection(const AsioTcpConnection &);
        ~AsioTcpConnection();
        static pointer_t create(asio::io_context& io_context, std::deque<pointer_t> &);
        void start();
        void handleWrite(const asio::error_code& /*error*/, size_t /*bytes_transferred*/);
        void HandleReadHeader(const asio::error_code &, std::size_t);
        void HandleReadData(const asio::error_code &, std::size_t);
        void interpret();
        const std::shared_ptr<asio::ip::tcp::socket> getSocket() const;
        const std::string &getUserName() const;
        const std::string &getUserContactList() const;
        int Login(const std::string &, const std::string &);
        int NewUser(const std::string &, const std::string &);
        void addContact(const std::string &new_c, const std::string &your_name);
    private:
        std::string _message;
        packet_t _packet;
        char _buffer[2048] = {0};
        std::deque<pointer_t> &_list;
};

#endif /* !ASIOTCPCONNECTION_HPP_ */