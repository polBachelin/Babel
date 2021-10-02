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

#define MAGIC 388474

typedef struct packet_info {
    int magic;
    int code;
    int data_size;
} packet_info_t;

typedef struct packet {
    int magic;
    int code;
    int data_size;
    char data[2048] = {0};
} packet_t;

class Commands;
typedef std::function<void(UserManager &um, packet_t &pck)> cmd_ptr;
class Commands {
    public:
        Commands() = default;
        ~Commands() = default;
        static void redirect(UserManager &um, packet_t &pck);

    protected:
    private:
        static void login(UserManager &um, packet_t &pck);
        static void register_(UserManager &um, packet_t &pck);
        static void add_contact(UserManager &um, packet_t &pck);
        static void call_X(UserManager &um, packet_t &pck);
        static const std::map<std::size_t, cmd_ptr> _cmd_map;
};

#endif /* !COMMANDS_HPP_ */
