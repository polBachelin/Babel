/*
** EPITECH PROJECT, 2021
** babel
** File description:
** ITcpConnection
*/

#ifndef ITCPCONNECTION_HPP_
#define ITCPCONNECTION_HPP_

#include "Commands.hpp"

class ITcpConnection {
    public:
        virtual void start() = 0;
        virtual void interpret() = 0;

    protected:
    private:
};

#endif /* !ITCPCONNECTION_HPP_ */
