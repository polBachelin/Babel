/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#include "CommandsManager.hpp"

const std::map<std::size_t, cmd_ptr> CommandsManager::_cmdMap = {
    {0, CommandsManager::login},
    {1, CommandsManager::registerUser},
    {2, CommandsManager::addContact},
    {112, CommandsManager::acceptInvitation},
    {3, CommandsManager::callX},
    {4, CommandsManager::listContact},
    {203, CommandsManager::callRefused}
};


pck_list *CommandsManager::redirect(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    try {
        std::cout << "---------Receive------------" << std::endl;
        PRINT_PCK((pck));
        std::cout << "----------------------------" << std::endl;
        if (pck.magic == MAGIC)
            return _cmdMap.at(pck.code)(pck, clients, currentClient);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        std::cout << "---------NULLLLL------------" << std::endl;
        return nullptr;
    }
    std::cout << "---------NULLLLLL------------" << std::endl;
    return nullptr;
}

pck_list *CommandsManager::createPacket(pck_list &l, std::shared_ptr<asio::ip::tcp::socket> s, int code, const std::string &data)
{
    packet_t *tmp = new packet_t;

    tmp->magic = MAGIC;
    tmp->code = code;
    tmp->data_size = data.length();
    tmp->data.fill(0);
    std::strcpy(tmp->data.data(), data.c_str());
    std::cout << "---------Packet created------------" << std::endl;
    PRINT_PCK((*tmp));
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "create " << s->is_open() << std::endl;
    auto sal = std::make_pair(s, tmp);
    l.push_back(sal);
    return nullptr;
}

pck_list *CommandsManager::login(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    std::string tmp = pck.data.data();
    std::array<std::string, 2> res;
    int value = 0;
    pck_list *pack = new pck_list;

    std::cout << "Login" << std::endl;
    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = currentClient.getUserManager().login(res[0], res[1]);
    if (value) {
        CommandsManager::createPacket(*pack, currentClient.getSocket(), 100, currentClient.getUserManager().getName());
        std::cout << "login " << pack->begin()->first->is_open() << std::endl;
    } else {
        CommandsManager::createPacket(*pack, currentClient.getSocket(), 200, "failed\n");
        std::cout << "login " << pack->begin()->first->is_open() << std::endl;
    }
    return pack;
}

pck_list *CommandsManager::registerUser(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    std::string tmp = pck.data.data();
    std::array<std::string, 2> res;
    int value = 0;
    pck_list *pack = new pck_list;

    res[0] = tmp.substr(0, tmp.find("\n"));
    tmp.erase(0, tmp.find("\n") + 1);
    res[1] = tmp;
    value = currentClient.getUserManager().newUser(res[0], res[1]);
    if (value == true) {
        CommandsManager::createPacket(*(pack), currentClient.getSocket(), 101, currentClient.getUserManager().getName());
    } else {
        CommandsManager::createPacket(*pack, currentClient.getSocket(), 201, "failed\n");
    }
    return pack;
}

pck_list *CommandsManager::addContact(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    auto name = currentClient.getUserManager().getName();
    std::string res = pck.data.data();
    std::string own;
    pck_list *pack = new pck_list;

    res.erase(res.find('\n'));
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->getUserManager().getName() == res) {
            auto dest = (*it)->getSocket();
            own = currentClient.getUserManager().getName() + "\n";
            CommandsManager::createPacket(*pack, dest, 12, own);
            CommandsManager::createPacket(*pack, currentClient.getSocket(), 102, res);
            return pack;
        }
    }
    CommandsManager::createPacket(*pack, currentClient.getSocket(), 202, "failed");
    return pack;
}

pck_list *CommandsManager::callX(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    std::string s = pck.data.data();
    std::string delimiter = "\n";
    size_t pos = 0;
    std::string token;
    std::array<std::string, 3> arr;
    int i = 0;
    std::string res;
    auto inc = currentClient.getSocket();
    pck_list *pack = new pck_list;

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        arr[i] = token;
        s.erase(0, pos + delimiter.length());
        i++;
    }
    std::cout << "Call " << arr[0] << " at " << arr[1] << ":" << arr[2] << std::endl;
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->getUserManager().getName() == arr[0]) {
            auto dest = (*it)->getSocket();
            std::cout << "Parent address in CALLX : " << inc->local_endpoint().address().to_string() << std::endl;
            res = currentClient.getUserManager().getName() + "\n" + arr[1] + "\n" + arr[2] + "\n";
            CommandsManager::createPacket(*pack, dest, 303, res);
            CommandsManager::createPacket(*pack, currentClient.getSocket(), 666, "");
            return pack;
        }
    }
    CommandsManager::createPacket(*pack, currentClient.getSocket(), 603, "failed\n");
    return pack;
}

pck_list *CommandsManager::listContact(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    //auto name = currentClient.getUserManager().getName();
    std::string res;
    std::string name = pck.data.data();
    pck_list *pack = new pck_list;


    name.erase(name.find('\n'));
    res = currentClient.getUserManager().getContactManager().getContactList();
    std::cout << "Res contact list : " << res << std::endl;
    CommandsManager::createPacket(*pack, currentClient.getSocket(), 4, res);
    return pack;
}

pck_list *CommandsManager::callRefused(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    std::string s = pck.data.data();
    auto inc = currentClient.getSocket();
    pck_list *pack = new pck_list;

    s.erase(s.find('\n'));
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->getUserManager().getName() == s) {
            auto dest = (*it)->getSocket();
            s = currentClient.getUserManager().getName() + "\n" + inc->local_endpoint().address().to_string() + "\n" + std::to_string(inc->local_endpoint().port()) + "\n";
            CommandsManager::createPacket(*pack, dest, 203, s);
            CommandsManager::createPacket(*pack, currentClient.getSocket(), 666, "");
            return pack;
        }
    }
    CommandsManager::createPacket(*pack, currentClient.getSocket(), 666, "");
    return pack;
}

pck_list *CommandsManager::acceptInvitation(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, ClientManager &currentClient)
{
    auto name = currentClient.getUserManager().getName();
    std::string res = pck.data.data();
    std::string own;
    pck_list *pack = new pck_list;

    res.erase(res.find('\n'));
    currentClient.getUserManager().getContactManager().addContact(res, name);
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->getUserManager().getName() == res) {
            auto dest = (*it)->getSocket();
            own = currentClient.getUserManager().getName() + "\n";
            CommandsManager::createPacket(*pack, dest, 302, own);
            CommandsManager::createPacket(*pack, currentClient.getSocket(), 666, "");
            return pack;
        }
    }
    CommandsManager::createPacket(*pack, currentClient.getSocket(), 666, "");
    return pack;
}
