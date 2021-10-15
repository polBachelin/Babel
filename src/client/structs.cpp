/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** structs
*/

#include "structs.hpp"

std::ostream &Client::operator<<(std::ostream &os, const Client::packet_t &pck) {
	os << "packet.magic     : " << pck.magic << std::endl;
	os << "packet.code      : " << pck.code << std::endl;
	os << "packet.data_size : " << pck.data_size << std::endl;
	os << "packet.data      : " << pck.data << std::endl;
	return os;
}
