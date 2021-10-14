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
#include <array>
#include <deque>
#include <ctime>
#include "ClientManager.hpp"

#define PRINT_PCK(pck) (std::cout << "Magic : " << pck.magic << "\nCode : " << pck.code << "\nData size :" << pck.data_size << "\nData : " << pck.data.data() << std::endl)

#define MAGIC 388474

typedef std::deque<std::pair<std::shared_ptr<asio::ip::tcp::socket>, packet_t *>> pck_list;
typedef std::function<pck_list *(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &, std::shared_ptr<ClientManager>)> cmd_ptr;
class CommandsManager {
    public:
        CommandsManager() = default;
        ~CommandsManager() = default;
        static pck_list *redirect(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &, std::shared_ptr<ClientManager>);
        static pck_list *createPacket(pck_list &l, std::shared_ptr<asio::ip::tcp::socket> s, int code, const std::string &data);

        static pck_list *login(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &, std::shared_ptr<ClientManager>);
        static pck_list *registerUser(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient);
        static pck_list *addContact(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient);
        static pck_list *acceptInvitation(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient);
        static pck_list *callX(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient);
        static pck_list *callRefused(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient);
        static pck_list *listContact(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient);
    private:
        static const std::map<std::size_t, cmd_ptr> _cmdMap;
};

#endif /* !COMMANDS_HPP_ */
