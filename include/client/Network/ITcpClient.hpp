/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** ITcpClient
*/

#ifndef ITCPCLIENT_HPP_
#define ITCPCLIENT_HPP_

#include <string>


namespace Client
{
    namespace Network
    {
        class ITcpClient
        {
            public:
                virtual void connectToHost() = 0;
                virtual void send(const char *) = 0;
                virtual void closeConnection() = 0;
                virtual void readyForRead() = 0;
                virtual void connected() = 0;
                virtual void connectionTimeout() = 0;
                virtual bool getStatus() = 0;
        };
    }
}

#endif /* !ITCPCLIENT_HPP_ */

