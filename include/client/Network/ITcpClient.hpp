/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** ITcpClient
*/

#ifndef ITCPCLIENT_HPP_
#define ITCPCLIENT_HPP_

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

