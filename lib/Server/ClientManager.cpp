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
	//std::cout << *packet << std::endl;
	_packet.code = packet->code;
	_packet.data = packet->data;
	_packet.data_size = packet->data_size;
	_packet.magic = packet->magic;
	//std::cout << _packet << std::endl;
}

void ClientManager::setPacketData(const std::array<char, 2048> &data)
{
	_packet.data = data;
}

std::ostream &operator<<(std::ostream &os, const packet_t &pck) {
	os << "------PACKET------" << std::endl;
	os << "packet.code : " << pck.code << std::endl;
	os << "packet.magic : " << pck.magic << std::endl;
	os << "packet.data_size : " << pck.data_size << std::endl;
	os << "packet.data : " << pck.data.data() << std::endl;
	return os;
}
