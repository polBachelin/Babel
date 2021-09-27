/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include "TcpConnection.hpp"
#include <map>
#include <functional>
#include <utility>

class Commands;
typedef std::function<void(packet_t *pck)> cmd_ptr;
class Commands {
    public:
        Commands() = default;
        ~Commands() = default;

    protected:
    private:
        static void login(packet_t *pck);
        static void register_(packet_t *pck);
        static void add_contact(packet_t *pck);
        static void call_X(packet_t *pck);
        static const std::map<std::size_t, cmd_ptr> _cmd_map;
};

#endif /* !COMMANDS_HPP_ */
