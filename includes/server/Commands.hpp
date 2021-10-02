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
typedef std::function<void(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)> cmd_ptr;
class Commands {
    public:
        Commands() = default;
        ~Commands() = default;
        static void redirect(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck);
    protected:
    private:
        static void sendResponse(asio::ip::tcp::socket &s, int code, const std::string &data);
        void HandleWrite(const asio::error_code &e, std::size_t bytes);
        static void login(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck);
        static void register_(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck);
        static void add_contact(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck);
        static void call_X(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck);
        static const std::map<std::size_t, cmd_ptr> _cmd_map;
};

#endif /* !COMMANDS_HPP_ */
