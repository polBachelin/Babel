/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** ITcpClient
*/

#ifndef ITCPCLIENT_HPP_
#define ITCPCLIENT_HPP_

#include <string>

typedef struct packet {
    int magic;
    int code;
    int data_size;
    char data[2048] = {0};
}packet_t;


namespace Client
{
    namespace Network
    {
        class ITcpClient
        {
            public:
                virtual void connectToHost() = 0;
                virtual void send(const std::string) = 0;
                virtual void closeConnection();
                virtual void readyRead() = 0;
            protected:
        };
    }
}

#endif /* !ITCPCLIENT_HPP_ */

