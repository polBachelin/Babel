/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** ClientManager
*/

#ifndef PACKETMANAGER_HPP_
#define PACKETMANAGER_HPP_

#include "UserManager.hpp"
#include <asio.hpp>
#include <memory>
#include <string>
#include <array>

typedef struct packet_info {
    int magic;
    int code;
    int data_size;
} packet_info_t;

typedef struct packet {
    int magic;
    int code;
    int data_size;
    std::array<char, 2048> data;
} packet_t;

class ClientManager {
	public:
		ClientManager(std::shared_ptr<asio::ip::tcp::socket> socket);
		~ClientManager();

		UserManager getUserManager() const;
		std::shared_ptr<asio::ip::tcp::socket> getSocket() const;
		packet_t getPacket() const;
		void setPacket(const packet_t &packet);
		void setPacketData(const std::array<char, 2048> &data);
	private:
		std::shared_ptr<asio::ip::tcp::socket> _userSocket;
		UserManager _um;
		packet_t _packet;
};

#endif /* !PACKETMANAGER_HPP_ */
