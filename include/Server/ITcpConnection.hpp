/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ITcpConnection
*/

#ifndef ITCPCONNECTION_HPP_
#define ITCPCONNECTION_HPP_

class ITcpConnection {
    public:
        virtual ~ITcpConnection() = default;
        virtual void start() = 0;
        virtual void interpret() = 0;
        
};

#endif /* !ITCPCONNECTION_HPP_ */
