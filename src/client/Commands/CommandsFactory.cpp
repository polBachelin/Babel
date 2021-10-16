/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CommandsFactory
*/

#include "CommandsFactory.hpp"

using namespace Client;

char *createBuffer(ClientInfos info, GUI::signal_e e, std::string data)
{
	packet_t package;
	char *buffTemp = new char[sizeof(package)];

	package.magic = MAGIC;
	package.code = e;
	package.data_size = data.size();
	strcpy(package.data, data.c_str());

	std::cout << "------------J'ai Envoyé----------------" << std::endl;
	std::cout << package;
	std::cout << "---------------------------------------" << std::endl;

	memcpy(buffTemp, &package, sizeof(package));
	return buffTemp;
}

const std::unordered_map<GUI::signal_e,
std::function<char *(ClientInfos, GUI::signal_e)>> CommandsFactory::_commands
{
	{GUI::signal_e::Elogin,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of login to server" << std::endl;
		return createBuffer(infos, e, infos.username + "\n" + infos.password + "\n");
	}},

	{GUI::signal_e::Elogout,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of logout to server" << std::endl;
		return createBuffer(infos, e, infos.username + "\n");
	}},

	{GUI::signal_e::Eregister,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of register to server" << std::endl;
		return createBuffer(infos, e, infos.username + "\n" + infos.password + "\n");
	}},

	{GUI::signal_e::Eaddcontact,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of addContact to server" << std::endl;
		return createBuffer(infos, e, infos.username + "\n");
	}},

	{GUI::signal_e::Erefuseincomingcall,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of refuse incoming call to server" << std::endl;
		return createBuffer(infos, e, infos.username + "\n");
	}},

	{GUI::signal_e::EcallX,
	[] (ClientInfos infos, GUI::signal_e e) {
		std::cout << "Telling server to call X" << std::endl;
		return createBuffer(infos, e, infos.userToCall + "\n" + infos.ip + "\n6000\n");
	}},

	{GUI::signal_e::Easkcontactlist,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of ask contact list to server" << std::endl;
		return createBuffer(infos, e, infos.username + "\n");
	}}
};

char *CommandsFactory::callCommand(ClientInfos info, GUI::signal_e e)
{
    if (_commands.find(e) == _commands.end()) {
        std::cout << "unknown call command code : " << e << std::endl;
		return NULL;
    } else {
        std::cout << "call command with code : " << e << std::endl;
		return _commands.at(e)(info, e);
    }
}
