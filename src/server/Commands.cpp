/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#include "Commands.hpp"

const std::map<std::size_t, cmd_ptr> Commands::_cmd_map = {
    {000, Commands::login},
    {001, Commands::Register},
    {002, Commands::addContact},
    {003, Commands::callX},
    {004, Commands::ListContact}
};

void Commands::redirect(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{
    try {
        _cmd_map.at(pck.code)(s, um, pck);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Commands::sendResponse(asio::ip::tcp::socket &s, int code, const std::string &data)
{
    packet_t response;
    packet_t *tmp = &response;
    asio::error_code e;

    tmp->magic = MAGIC;
    tmp->code = 200;
    tmp->data_size = data.length();
    std::strcpy(tmp->data, data.c_str());
}

void Commands::HandleWrite(const asio::error_code &e, std::size_t bytes)
{
}

void Commands::login(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{
    std::string tmp = pck.data;
    std::array<std::string, 2> res;
    int value = 0;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = um.login(res[0], res[1]);
    if (value == true) {
        Commands::sendResponse(s, 100, "success\n");
    } else {
        Commands::sendResponse(s, 200, "failed\n");
    }
}

void Commands::Register(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{
    std::string tmp = pck.data;
    std::array<std::string, 2> res;
    int value = 0;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = um.new_user(res[0], res[1]);
    if (value == true) {
        Commands::sendResponse(s, 101, um.GetName());
    } else {
        Commands::sendResponse(s, 201, "failed\n");
    }
}

void Commands::addContact(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{
    auto tmp = um.GetContactManager();
    auto name = um.GetName();
    std::string res = pck.data;
    
    res.erase(res.find('\n'));
    tmp.addContact(res, name);
}

void Commands::callX(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{
}

void Commands::ListContact(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{
    auto tmp = um.GetContactManager();
    auto name = um.GetName();
    std::string res;
    
    res = tmp.getContactList(name);
    sendResponse(s, 004, res);
}