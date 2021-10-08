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

packet_t *Commands::redirect(UserManager &um, packet_t &pck)
{
    try {
        return _cmd_map.at(pck.code)(um, pck);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return nullptr;
}

packet_t *Commands::CreatePacket(int code, const std::string &data)
{
    packet_t response;
    packet_t *tmp = &response;

    tmp->magic = MAGIC;
    tmp->code = code;
    tmp->data_size = data.length();
    std::strcpy(tmp->data, data.c_str());
    return tmp;
}

packet_t *Commands::login(UserManager &um, packet_t &pck)
{
    std::string tmp = pck.data;
    std::array<std::string, 2> res;
    int value = 0;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = um.login(res[0], res[1]);
    if (value == true) {
        return Commands::CreatePacket(100, "success\n");
    } else {
        return Commands::CreatePacket(200, "failed\n");
    }
}

packet_t *Commands::Register(UserManager &um, packet_t &pck)
{
    std::string tmp = pck.data;
    std::array<std::string, 2> res;
    int value = 0;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = um.new_user(res[0], res[1]);
    if (value == true) {
        return Commands::CreatePacket(101, um.GetName());
    } else {
        return Commands::CreatePacket(201, "failed\n");
    }
}

packet_t *Commands::addContact(UserManager &um, packet_t &pck)
{
    auto tmp = um.GetContactManager();
    auto name = um.GetName();
    std::string res = pck.data;
    
    res.erase(res.find('\n'));
    tmp.addContact(res, name);
    return Commands::CreatePacket(102, "success");
}

packet_t *Commands::callX(UserManager &um, packet_t &pck)
{
    return NULL;
}

packet_t *Commands::ListContact(UserManager &um, packet_t &pck)
{
    auto tmp = um.GetContactManager();
    auto name = um.GetName();
    std::string res;
    
    (void)pck;
    res = tmp.getContactList(name);
    return Commands::CreatePacket(004, res);
}