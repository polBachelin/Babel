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
    std::cout << "message sent " << asio::write(s, asio::buffer(tmp, sizeof(packet_t)), e) << std::endl;
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

void Commands::register_(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
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

void Commands::add_contact(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{

}

void Commands::call_X(asio::ip::tcp::socket &s, UserManager &um, packet_t &pck)
{
}
