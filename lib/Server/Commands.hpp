/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include "AAsioTcpConnection.hpp"

class Commands;
typedef std::function<packet_t *(UserManager &um, packet_t &pck, std::deque<pointer_t> &)> cmd_ptr;
class Commands {
    public:
        Commands() = default;
        ~Commands() = default;
        static packet_t *redirect(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static packet_t *CreatePacket(int code, const std::string &data);
    protected:
    private:
        static packet_t *login(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static packet_t *Register(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static packet_t *addContact(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static packet_t *AcceptInvitation(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static packet_t *callX(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static packet_t *callRefused(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static packet_t *ListContact(UserManager &um, packet_t &pck, std::deque<pointer_t> &);
        static const std::map<std::size_t, cmd_ptr> _cmd_map;
};

#endif /* !COMMANDS_HPP_ */
