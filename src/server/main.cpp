/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include "TcpServer.hpp"

int main(int ac, char **av)
{
    try {
        asio::io_context io;
        TcpServer server(io);
        io.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}