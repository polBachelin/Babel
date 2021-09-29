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

void Commands::redirect(packet_t &pck)
{
    try {
        _cmd_map.at(pck.code)(pck);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void Commands::login(packet_t &pck)
{

}

void Commands::register_(packet_t &pck)
{

}

void Commands::add_contact(packet_t &pck)
{

}

void Commands::call_X(packet_t &pck)
{
}
