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
    {004, Commands::ListContact},
    {203, Commands::callX}
};

packet_t *Commands::redirect(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    try {
        return _cmd_map.at(pck.code)(um, pck, list);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
    return nullptr;
}

packet_t *Commands::CreatePacket(int code, const std::string &data)
{
    packet_t *tmp = new packet_t;

    tmp->magic = MAGIC;
    tmp->code = code;
    std::cout << "DAta : " << data << " " << data.length() << std::endl;
    tmp->data_size = data.length();
    std::strcpy(tmp->data, data.c_str());
    return tmp;
}

packet_t *Commands::login(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    std::string tmp = pck.data;
    std::array<std::string, 2> res;
    int value = 0;

    std::cout << "Login" << std::endl;
    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = um.login(res[0], res[1]);
    if (value) {
        return Commands::CreatePacket(100, um.GetName());
    } else {
        return Commands::CreatePacket(200, "failed\n");
    }
}

packet_t *Commands::Register(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
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

packet_t *Commands::addContact(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    auto tmp = um.GetContactManager();
    auto name = um.GetName();
    std::string res = pck.data;
    
    res.erase(res.find('\n'));
    tmp.addContact(res, name);
    return Commands::CreatePacket(102, "success");
}

packet_t *Commands::callX(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    std::string s = pck.data;
    std::string delimiter = "\n";
    size_t pos = 0;
    std::string token;
    std::array<std::string, 3> arr;
    int i = 0;
    std::string res;
    asio::ip::tcp::socket &inc = um.getSock();

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        arr[i] = token;
        s.erase(0, pos + delimiter.length());
        i++;
    }
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUsermanager().GetName() == arr[0]) {
            asio::ip::tcp::socket &dest = (*it)->getUsermanager().getSock();
            res = um.GetName() + "\n" + inc.local_endpoint().address().to_string() + "\n" + arr[2] + "\n";
            auto tmp = Commands::CreatePacket(303, res);
            dest.write_some(asio::buffer(tmp, sizeof(packet_t)));
            return Commands::CreatePacket(666, "");
        }
    }
    return Commands::CreatePacket(666, "");
}

packet_t *Commands::ListContact(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    auto tmp = um.GetContactManager();
    auto name = um.GetName();
    std::string res;
    
    (void)pck;
    res = tmp.getContactList(name);
    return Commands::CreatePacket(004, res);
}

packet *Commands::callRefused(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    std::string s = pck.data;
    asio::ip::tcp::socket &inc = um.getSock();

    s.erase(s.find('\n'));
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUsermanager().GetName() == s) {
            asio::ip::tcp::socket &dest = (*it)->getUsermanager().getSock();
            s = um.GetName() + "\n" + inc.local_endpoint().address().to_string() + "\n" + std::to_string(inc.local_endpoint().port()) + "\n";
            auto tmp = Commands::CreatePacket(303, s);
            dest.write_some(asio::buffer(tmp, sizeof(packet_t)));
            return Commands::CreatePacket(666, "");
        }
    }
    return Commands::CreatePacket(666, "");    
}