/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** APage
*/

#include "APage.hpp"

Client::GUI::APage::APage(ClientInfos infos, QWidget *parent) : QWidget(parent) ,_infos(infos)
{
}

void Client::GUI::APage::setClientInfos(const ClientInfos &infos)
{
    _infos = infos;
}

std::ostream &operator<<(std::ostream &os, const Client::packet_t &pck) {
	os << "packet.magic     : " << pck.magic << std::endl;
	os << "packet.code      : " << pck.code << std::endl;
	os << "packet.data_size : " << pck.data_size << std::endl;
	os << "packet.data      : " << pck.data << std::endl;
	return os;
}

#include "moc_APage.cpp"
