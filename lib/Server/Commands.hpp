/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#ifndef COMMANDS_HPP_
#define COMMANDS_HPP_

#include "AAsioTcpConnection.hpp"
#define PRINT_PCK(pck) (std::cout << "Magic : " << pck.magic << "\nCode : " << pck.code << "\nData size :" << pck.data_size << "\nData : " << pck.data.data() << std::endl)

class Commands;
typedef std::deque<std::pair<std::shared_ptr<asio::ip::tcp::socket>, packet_t *>> pck_list;
typedef std::function<pck_list *(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &)> cmd_ptr;
class Commands {
    public:
        Commands() = default;
        ~Commands() = default;
        static pck_list *redirect(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static pck_list *CreatePacket(pck_list &l, std::shared_ptr<asio::ip::tcp::socket> s, int code, const std::string &data);
    protected:
    private:
        static pck_list *login(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static pck_list *Register(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static pck_list *addContact(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static pck_list *AcceptInvitation(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static pck_list *callX(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static pck_list *callRefused(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static pck_list *ListContact(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &);
        static const std::map<std::size_t, cmd_ptr> _cmd_map;
};

#endif /* !COMMANDS_HPP_ */
