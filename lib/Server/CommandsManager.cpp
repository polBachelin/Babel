/*
** EPITECH PROJECT, 2021
** babel
** File description:
** Commands
*/

#include "CommandsManager.hpp"

const std::unordered_map<std::size_t, cmd_ptr> CommandsManager::_cmdMap = {
    {LOGIN, CommandsManager::login},
    {REGISTER, CommandsManager::registerUser},
    {ADD_CONTACT, CommandsManager::addContact},
    {CALL, CommandsManager::callX},
    {ASK_CONTACT_LIST, CommandsManager::listContact},
    {LOGOUT, CommandsManager::logout},
    {CALL_WAS_REFUSE, CommandsManager::callRefused},
    {ASK_MESSAGE_HISTORY, CommandsManager::listMessage},
    {NEW_MESSAGE, CommandsManager::newMessage}
};

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.length() > 0) {
            elems.push_back(item);
        }
    }
    return elems;
}


pck_list *CommandsManager::redirect(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager> currentClient)
{
    try {
        if (pck.code != 4 && pck.magic == MAGIC) {
            std::cout << "---------Receive------------" << std::endl;
            std::cout << pck;
            std::cout << "----------------------------" << std::endl;
        }
        if (pck.magic == MAGIC)
            return _cmdMap.at(pck.code)(pck, clients, currentClient);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
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
    auto sal = std::make_pair(s, tmp);
    l.push_back(sal);
    return nullptr;
}

pck_list *CommandsManager::login(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager> currentClient)
{
    (void)clients;
    std::string tmp = pck.data.data();
    std::vector<std::string> elem;
    std::string res;
    pck_list *pack = new pck_list;
    int value = 0;

    elem = split(pck.data.data(), '\n', elem);
    value = currentClient->_um.login(elem[0], elem[1]);
    if (value) {
        CommandsManager::createPacket(*pack, currentClient->getSocket(), LOGIN_SUCCESS, currentClient->_um.getName());
    } else {
        CommandsManager::createPacket(*pack, currentClient->getSocket(), LOGIN_FAILED, "failed\n");
    }
    return pack;
}

pck_list *CommandsManager::registerUser(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager> currentClient)
{
    (void)clients;
    std::string tmp = pck.data.data();
    std::vector<std::string> elem;
    std::string res;
    int value = 0;
    pck_list *pack = new pck_list;

    elem = split(pck.data.data(), '\n', elem);
    value = currentClient->_um.newUser(elem[0], elem[1]);
    if (value == true) {
        CommandsManager::createPacket(*(pack), currentClient->getSocket(), REGISTER_SUCCESS, currentClient->_um.getName());
    } else {
        CommandsManager::createPacket(*pack, currentClient->getSocket(), REGISTER_FAILED, "failed\n");
    }
    return pack;
}

pck_list *CommandsManager::addContact(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager> currentClient)
{
    auto name = currentClient->_um.getName();
    std::vector<std::string> elem;
    std::string res;
    std::string own;
    pck_list *pack = new pck_list;

    elem = split(pck.data.data(), '\n', elem);
    res = elem[0];
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->_um.getName() == res) {
            currentClient->getUserManager().getContactManager().addContact(name, res);
            auto dest = (*it)->getSocket();
            own = currentClient->_um.getName() + "\n";
            CommandsManager::createPacket(*pack, dest, INVTATION_RECEIVE, own);
            CommandsManager::createPacket(*pack, currentClient->getSocket(), CONTACT_EXIST, res);
            return pack;
        }
    }
    CommandsManager::createPacket(*pack, currentClient->getSocket(), CONTACT_ADD_FAILED, "failed");
    return pack;
}

pck_list *CommandsManager::callX(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager> currentClient)
{
    std::string s = pck.data.data();
    auto inc = currentClient->getSocket();
    pck_list *pack = new pck_list;
    std::vector<std::string> elem;
    std::string res;

    elem = split(pck.data.data(), '\n', elem);
    std::cout << "Call " << elem[0] << " at " << elem[1] << ":" << elem[2] << std::endl;
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->_um.getName() == elem[0]) {
            auto dest = (*it)->getSocket();
            std::cout << "Parent address in CALLX : " << inc->local_endpoint().address().to_string() << std::endl;
            res = currentClient->_um.getName() + "\n" + elem[1] + "\n" + elem[2] + "\n";
            CommandsManager::createPacket(*pack, dest, INCOMING_CALL, res);
            CommandsManager::createPacket(*pack, currentClient->getSocket(), DONT_SEND, "");
            return pack;
        }
    }
    CommandsManager::createPacket(*pack, currentClient->getSocket(), USER_NOT_FOUND, "failed\n");
    return pack;
}

pck_list *CommandsManager::listContact(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager> currentClient)
{
    //auto name = currentClient->_um.getName();
    std::string res;
    std::string name = pck.data.data();
    pck_list *pack = new pck_list;
    std::vector<std::string> arg;

    arg = split(name, '\n', arg);
    res = currentClient->_um.getContactManager().getContactList(arg[0]);
    arg.clear();
    arg = split(res, '\n', arg);
    res = "";
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        for (auto its = arg.begin(); its != arg.end(); ++its) {
            if ((*it)->_um.getName() == *its) {
                res += *its + "\n";
            }
        }
    }
    CommandsManager::createPacket(*pack, currentClient->getSocket(), CONTACT_LIST, res);
    return pack;
}

pck_list *CommandsManager::callRefused(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager> currentClient)
{
    auto inc = currentClient->getSocket();
    pck_list *pack = new pck_list;
    std::vector<std::string> elem;
    std::string res;

    elem = split(pck.data.data(), '\n', elem);
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->_um.getName() == elem[0]) {
            auto dest = (*it)->getSocket();
            elem[0] = currentClient->_um.getName() + "\n" + inc->local_endpoint().address().to_string() + "\n" + std::to_string(inc->local_endpoint().port()) + "\n";
            CommandsManager::createPacket(*pack, dest, CALL_REFUSED, elem[0] + "\n");
            CommandsManager::createPacket(*pack, currentClient->getSocket(), DONT_SEND, "");
            return pack;
        }
    }
    CommandsManager::createPacket(*pack, currentClient->getSocket(), DONT_SEND, "");
    return pack;
}

pck_list *CommandsManager::logout(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient)
{
    (void)pck;
    (void)clients;
    currentClient->clearPacket();
    currentClient->_um.logoutUser();
    return nullptr;
}

pck_list *CommandsManager::listMessage(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient)
{
    pck_list *pack = new pck_list;
    std::vector<std::string> elem;
    std::deque<std::string> messageHistory;

    (void)clients;
    elem = split(pck.data.data(), '\n', elem);
    messageHistory = currentClient->_um.getMessageManager().getHistory(elem[0], elem[1]);
    for (auto &it : messageHistory) {
        CommandsManager::createPacket(*pack, currentClient->getSocket(), SEND_ONE_MESSAGE, it);
    }
    return pack;
}

pck_list *CommandsManager::newMessage(const packet_t &pck, std::deque<std::shared_ptr<ClientManager>> &clients, std::shared_ptr<ClientManager>currentClient)
{
    pck_list *pack = new pck_list;
    std::vector<std::string> elem;
    std::string res;

    elem = split(pck.data.data(), '\n', elem);
    currentClient->_um.getMessageManager().newMessage(elem[0], elem[1], elem[2]);
    res = currentClient->_um.getMessageManager().getHistory(elem[0], elem[1]).back();
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        if ((*it)->_um.getName() == elem[1]) {
            CommandsManager::createPacket(*pack, currentClient->getSocket(), SEND_ONE_MESSAGE, res);
            CommandsManager::createPacket(*pack, (*it)->getSocket(), SEND_ONE_MESSAGE, res);
        }
    }
    return pack;
}
