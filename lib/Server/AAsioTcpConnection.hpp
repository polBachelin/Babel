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

        virtual asio::ip::tcp::socket &socket() = 0;
        virtual void start() = 0;
        virtual UserManager &getUsermanager() = 0;

    protected:
    private:
};

#endif /* !AASIOTCPCONNECTION_HPP_ */
