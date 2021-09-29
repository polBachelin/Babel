/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** ITcpClient
*/

#ifndef ITCPCLIENT_HPP_
#define ITCPCLIENT_HPP_

#include <iostream>

namespace Client
{
    namespace Network
    {
        class ITcpClient {
            public:
                ITcpClient();
                ~ITcpClient();
                virtual bool send(const unsigned char *, std::size_t size) const = 0;
                virtual std::pair<std::size_t, const unsigned char *> getData() = 0;
                virtual void connectSocket(const std::string, unsigned short) = 0;
                virtual bool isConnected() = 0;

            protected:
            private:
        };
    }

#endif /* !ITCPCLIENT_HPP_ */

