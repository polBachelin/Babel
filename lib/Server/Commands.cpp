/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#include "Commands.hpp"

const std::map<std::size_t, cmd_ptr> Commands::_cmd_map = {
    {0, Commands::login},
    {1, Commands::Register},
    {2, Commands::addContact},
    {112, Commands::AcceptInvitation},
    {3, Commands::callX},
    {4, Commands::ListContact},
    {203, Commands::callRefused}
};

packet_t *Commands::redirect(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    try {
        std::cout << "---------Receive------------" << std::endl;
        PRINT_PCK((pck));
        std::cout << "----------------------------" << std::endl;
        if (pck.magic == MAGIC)
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
    tmp->data_size = data.length();
    std::strcpy(tmp->data, data.c_str());
    std::cout << "---------Packet created------------" << std::endl;
    PRINT_PCK((*tmp));
    std::cout << "-----------------------------------" << std::endl;
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
    std::string own;

    res.erase(res.find('\n'));
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUsermanager().GetName() == res) {
            asio::ip::tcp::socket &dest = (*it)->getUsermanager().getSock();
            own = um.GetName() + "\n";
            auto tmp = Commands::CreatePacket(12, own);
            dest.write_some(asio::buffer(tmp, sizeof(packet_t)));
            return Commands::CreatePacket(102, res);
        }
    }
    return Commands::CreatePacket(202, "failed");
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
    std::cout << "Call " << arr[0] << " at " << arr[1] << ":" << arr[2] << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUsermanager().GetName() == arr[0]) {
            asio::ip::tcp::socket &dest = (*it)->getUsermanager().getSock();
            res = um.GetName() + "\n" + inc.local_endpoint().address().to_string() + "\n" + arr[2] + "\n";
            auto tmp = Commands::CreatePacket(303, res);
            dest.write_some(asio::buffer(tmp, sizeof(packet_t)));
            return Commands::CreatePacket(666, "");
        }
    }
    return Commands::CreatePacket(603, "failed\n");
}

packet_t *Commands::ListContact(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    auto tmp = um.GetContactManager();
    //auto name = um.GetName();
    std::string res;
    std::string name = pck.data;


    name.erase(name.find('\n'));
    res = tmp.getContactList(name);
    std::cout << "Res contact list : " << res << std::endl;
    return Commands::CreatePacket(4, res);
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
            auto tmp = Commands::CreatePacket(203, s);
            dest.write_some(asio::buffer(tmp, sizeof(packet_t)));
            return Commands::CreatePacket(666, "");
        }
    }
    return Commands::CreatePacket(666, "");
}

packet_t *Commands::AcceptInvitation(UserManager &um, packet_t &pck, std::deque<pointer_t> &list)
{
    auto tmp = um.GetContactManager();
    auto name = um.GetName();
    std::string res = pck.data;
    std::string own;

    res.erase(res.find('\n'));
    tmp.addContact(res, name);
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUsermanager().GetName() == res) {
            asio::ip::tcp::socket &dest = (*it)->getUsermanager().getSock();
            own = um.GetName() + "\n";
            auto tmp = Commands::CreatePacket(302, own);
            dest.write_some(asio::buffer(tmp, sizeof(packet_t)));
            return Commands::CreatePacket(666, "");
        }
    }
    return Commands::CreatePacket(666, "");
}
