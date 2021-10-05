/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ITcpServer
*/

#ifndef ITCPSERVER_HPP_
#define ITCPSERVER_HPP_

class ITcpServer {
    public:
        virtual ~ITcpServer() = default;
        virtual void startAccept() = 0;
        virtual void initServer(int port) = 0;
};

#endif /* !ITCPSERVER_HPP_ */
