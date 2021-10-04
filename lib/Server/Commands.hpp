/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include <map>
#include <functional>
#include <utility>
#include <iostream>
#include <asio.hpp>
#include <array>
#include <deque>
#include <ctime>
#include <memory>
#include "UserManager.hpp"

class Commands;
typedef std::function<packet_t *(UserManager &um, packet_t &pck)> cmd_ptr;
class Commands {
    public:
        Commands() = default;
        ~Commands() = default;
        static packet_t *redirect(UserManager &um, packet_t &pck);
        static packet_t *CreatePacket(int code, const std::string &data);
    protected:
    private:
        static packet_t *login(UserManager &um, packet_t &pck);
        static packet_t *Register(UserManager &um, packet_t &pck);
        static packet_t *addContact(UserManager &um, packet_t &pck);
        static packet_t *callX(UserManager &um, packet_t &pck);
        static packet_t *ListContact(UserManager &um, packet_t &pck);
        static const std::map<std::size_t, cmd_ptr> _cmd_map;
};

#endif /* !COMMANDS_HPP_ */
