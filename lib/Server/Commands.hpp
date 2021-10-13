/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include "AAsioTcpConnection.hpp"
#define PRINT_PCK(pck) (std::cout << "Magic : " << pck.magic << "\nCode : " << pck.code << "\nData size :" << pck.data_size << "\nData : " << pck.data << std::endl)

class Commands;
typedef std::deque<std::pair<std::shared_ptr<asio::ip::tcp::socket>, packet_t *>> pck_list;
typedef std::function<pck_list *(pointer_t parent, packet_t &pck, std::deque<pointer_t> &)> cmd_ptr;
class Commands {
    public:
        Commands() = default;
        ~Commands() = default;
        static pck_list *redirect(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static pck_list *CreatePacket(pck_list &l, std::shared_ptr<asio::ip::tcp::socket> s, int code, const std::string &data);
    protected:
    private:
        static pck_list *login(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static pck_list *Register(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static pck_list *addContact(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static pck_list *AcceptInvitation(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static pck_list *callX(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static pck_list *callRefused(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static pck_list *ListContact(pointer_t parent, packet_t &pck, std::deque<pointer_t> &);
        static const std::map<std::size_t, cmd_ptr> _cmd_map;
};

#endif /* !COMMANDS_HPP_ */
