/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** ITcpClient
*/

#ifndef ITCPCLIENT_HPP_
#define ITCPCLIENT_HPP_

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
                virtual void start() = 0;
                virtual void stop() = 0;
            protected:
                virtual bool connectToServer() = 0;
        };
    }
}

#endif /* !ITCPCLIENT_HPP_ */

