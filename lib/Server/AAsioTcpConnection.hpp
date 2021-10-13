/*
** EPITECH PROJECT, 2021
** babel
** File description:
** IAsioTcpConnection
*/

#ifndef AASIOTCPCONNECTION_HPP_
#define AASIOTCPCONNECTION_HPP_

#include <map>
#include <functional>
#include <utility>
#include <iostream>
#include <asio.hpp>
#include <array>
#include <deque>
#include <ctime>
#include <memory>
#include "UserManager.hpp"
#include "ITcpConnection.hpp"

class AAsioTcpConnection;
typedef std::shared_ptr<AAsioTcpConnection> pointer_t;

class AAsioTcpConnection : public ITcpConnection {
    public:
        AAsioTcpConnection() = default;
        ~AAsioTcpConnection() = default;

        virtual void start() = 0;
        virtual const std::shared_ptr<asio::ip::tcp::socket> getSocket() const = 0;
        virtual const std::string &getUserName() const = 0;
        virtual const std::string &getUserContactList() const = 0;
        virtual int Login(const std::string &, const std::string &) = 0;
        virtual int NewUser(const std::string &, const std::string &) = 0;
        virtual void addContact(const std::string &new_c, const std::string &your_name) = 0;
    protected:
        std::shared_ptr<asio::ip::tcp::socket> _socket;
        UserManager _um;
    private:
};

#endif /* !AASIOTCPCONNECTION_HPP_ */
