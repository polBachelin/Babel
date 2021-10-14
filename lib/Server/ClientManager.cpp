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

UserManager ClientManager::getUserManager() const
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

void ClientManager::setPacket(const packet_t &packet)
{
	_packet = packet;
}

void ClientManager::setPacketData(const std::array<char, 2048> &data)
{
	_packet.data = data;
}