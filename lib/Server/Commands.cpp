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

pck_list *Commands::redirect(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    try {
        std::cout << "---------Receive------------" << std::endl;
        PRINT_PCK((pck));
        std::cout << "----------------------------" << std::endl;
        if (pck.magic == MAGIC)
            return _cmd_map.at(pck.code)(parent, pck, list);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "---------NULLLLL------------" << std::endl;
        return nullptr;
    }
    std::cout << "---------NULLLLLL------------" << std::endl;
    return nullptr;
}

pck_list *Commands::CreatePacket(pck_list &l, std::shared_ptr<asio::ip::tcp::socket> s, int code, const std::string &data)
{
    packet_t *tmp = new packet_t;

    tmp->magic = MAGIC;
    tmp->code = code;
    tmp->data_size = data.length();
    std::strcpy(tmp->data.data(), data.c_str());
    std::cout << "---------Packet created------------" << std::endl;
    PRINT_PCK((*tmp));
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "create " << s->is_open() << std::endl;
    auto sal = std::make_pair(s, tmp);
    l.push_back(sal);
    return nullptr;
}

pck_list *Commands::login(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    std::string tmp = pck.data.data();
    std::array<std::string, 2> res;
    int value = 0;
    pck_list *pack = new pck_list;

    std::cout << "Login" << std::endl;
    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = parent->Login(res[0], res[1]);
    if (value) {
        Commands::CreatePacket(*pack, parent->getSocket(), 100, parent->getUserName());
        std::cout << "login " << pack->begin()->first->is_open() << std::endl;
    } else {
        Commands::CreatePacket(*pack, parent->getSocket(), 200, "failed\n");
        std::cout << "login " << pack->begin()->first->is_open() << std::endl;
    }
    return pack;
}

pck_list *Commands::Register(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    std::string tmp = pck.data.data();
    std::array<std::string, 2> res;
    int value = 0;
    pck_list *pack = new pck_list;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = parent->NewUser(res[0], res[1]);
    if (value == true) {
        Commands::CreatePacket(*(pack), parent->getSocket(), 101, parent->getUserName());
    } else {
        Commands::CreatePacket(*pack, parent->getSocket(), 201, "failed\n");
    }
    return pack;
}

pck_list *Commands::addContact(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    auto name = parent->getUserName();
    std::string res = pck.data.data();
    std::string own;
    pck_list *pack = new pck_list;

    res.erase(res.find('\n'));
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUserName() == res) {
            auto dest = (*it)->getSocket();
            own = parent->getUserName() + "\n";
            Commands::CreatePacket(*pack, dest, 12, own);
            Commands::CreatePacket(*pack, parent->getSocket(), 102, res);
            return pack;
        }
    }
    Commands::CreatePacket(*pack, parent->getSocket(), 202, "failed");
    return pack;
}

pck_list *Commands::callX(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    std::string s = pck.data.data();
    std::string delimiter = "\n";
    size_t pos = 0;
    std::string token;
    std::array<std::string, 3> arr;
    int i = 0;
    std::string res;
    auto inc = parent->getSocket();
    pck_list *pack = new pck_list;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        arr[i] = token;
        s.erase(0, pos + delimiter.length());
        i++;
    }
    std::cout << "Call " << arr[0] << " at " << arr[1] << ":" << arr[2] << std::endl;
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUserName() == arr[0]) {
            auto dest = (*it)->getSocket();
            std::cout << "Parent address in CALLX : " << inc->local_endpoint().address().to_string() << std::endl;
            res = parent->getUserName() + "\n" + arr[1] + "\n" + arr[2] + "\n";
            Commands::CreatePacket(*pack, dest, 303, res);
            Commands::CreatePacket(*pack, parent->getSocket(), 666, "");
            return pack;
        }
    }
    Commands::CreatePacket(*pack, parent->getSocket(), 603, "failed\n");
    return pack;
}

pck_list *Commands::ListContact(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    //auto name = parent->getUserName();
    std::string res;
    std::string name = pck.data.data();
    pck_list *pack = new pck_list;


    name.erase(name.find('\n'));
    res = parent->getUserContactList();
    std::cout << "Res contact list : " << res << std::endl;
    Commands::CreatePacket(*pack, parent->getSocket(), 4, res);
    return pack;
}

pck_list *Commands::callRefused(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    std::string s = pck.data.data();
    auto inc = parent->getSocket();
    pck_list *pack = new pck_list;

    s.erase(s.find('\n'));
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUserName() == s) {
            auto dest = (*it)->getSocket();
            s = parent->getUserName() + "\n" + inc->local_endpoint().address().to_string() + "\n" + std::to_string(inc->local_endpoint().port()) + "\n";
            Commands::CreatePacket(*pack, dest, 203, s);
            Commands::CreatePacket(*pack, parent->getSocket(), 666, "");
            return pack;
        }
    }
    Commands::CreatePacket(*pack, parent->getSocket(), 666, "");
    return pack;
}

pck_list *Commands::AcceptInvitation(std::shared_ptr<AAsioTcpConnection> parent, packet_t &pck, std::deque<std::shared_ptr<AAsioTcpConnection>> &list)
{
    auto name = parent->getUserName();
    std::string res = pck.data.data();
    std::string own;
    pck_list *pack = new pck_list;

    res.erase(res.find('\n'));
    parent->addContact(res, name);
    for (auto it = list.begin(); it != list.end(); ++it) {
        if ((*it)->getUserName() == res) {
            auto dest = (*it)->getSocket();
            own = parent->getUserName() + "\n";
            Commands::CreatePacket(*pack, dest, 302, own);
            Commands::CreatePacket(*pack, parent->getSocket(), 666, "");
            return pack;
        }
    }
    Commands::CreatePacket(*pack, parent->getSocket(), 666, "");
    return pack;
}
