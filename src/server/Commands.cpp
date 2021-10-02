/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#include "Commands.hpp"

const std::map<std::size_t, cmd_ptr> Commands::_cmd_map = {
    {000, Commands::login},
    {001, Commands::register_},
    {002, Commands::add_contact},
    {003, Commands::call_X},
};

void Commands::redirect(UserManager &um, packet_t &pck)
{
    try {
        _cmd_map.at(pck.code)(um, pck);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Commands::login(UserManager &um, packet_t &pck)
{
    std::string tmp = pck.data;
    std::array<std::string, 2> res;
    int value = 0;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    std::cout << "username : " << res[0] << std::endl;
    std::cout << "passwd : " << res[1] << std::endl;
    value = um.login(res[0], res[1]);
}

void Commands::register_(UserManager &um, packet_t &pck)
{
    std::string tmp = pck.data;
    std::array<std::string, 2> res;
    int value = 0;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    std::cout << "username : " << res[0] << std::endl;
    std::cout << "passwd : " << res[1] << std::endl;
    value = um.new_user(res[0], res[1]);
}

void Commands::add_contact(UserManager &um, packet_t &pck)
{

}

void Commands::call_X(UserManager &um, packet_t &pck)
{
}
