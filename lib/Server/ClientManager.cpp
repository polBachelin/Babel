/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ClientManager
*/

#include "ClientManager.hpp"

ClientManager::ClientManager(std::shared_ptr<asio::ip::tcp::socket> socket)
: _userSocket(socket)
{
	_packet.code = 84;
    _packet.magic = 0;
    _packet.data_size = 0;
    _packet.data.fill(0);
}

ClientManager::~ClientManager()
{
}

UserManager ClientManager::getUserManager()
{
	return _um;
}

std::shared_ptr<asio::ip::tcp::socket> ClientManager::getSocket() const
{
	return _userSocket;
}

packet_t ClientManager::getPacket() const
{
	return _packet;
}

void ClientManager::setPacket(const packet_t *packet)
{
	_packet.code = packet->code;
	_packet.data = packet->data;
	_packet.data_size = packet->data_size;
	_packet.magic = packet->magic;
}

void ClientManager::setPacketData(const std::array<char, 2048> &data)
{
	_packet.data = data;
}

std::vector<std::string> convertCurrentData(std::string data, const char sep)
{
    std::replace(data.begin(), data.end(), sep, ' ');
    std::istringstream ss(data);
    std::pair<std::string, std::vector<std::string>> words;

    while (ss >> words.first)
        words.second.push_back(words.first);
    return words.second;
}

std::ostream &operator<<(std::ostream &os, const packet_t &pck)
{
    std::vector<std::string> data(convertCurrentData(std::string(pck.data.data()), '\n'));

    if (pck.code == 4)
        return os;
	os << "packet.magic     : " << pck.magic << std::endl;
	os << "packet.code      : " << pck.code << std::endl;
	os << "packet.data_size : " << pck.data_size << std::endl;
	os << "packet.data      : [";
    for (auto it = data.begin(); it != data.end(); it++) {
        os << *it << ((it == data.end() - 1) ? "]" : ", ");
    }
    return os << std::endl;
}

void ClientManager::clearPacket()
{
    _packet.magic = 0;
    _packet.code = 84;
    _packet.data_size = 0;
    _packet.data.fill('\0');
}