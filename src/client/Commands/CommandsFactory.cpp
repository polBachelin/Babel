/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CommandsFactory
*/

#include "CommandsFactory.hpp"

using namespace Client;

static char *createBuffer(GUI::signal_e e, std::string data)
{
	packet_t package;
	char *buffTemp = new char[sizeof(package)];

	std::memset(package.data, 0, 2048);
	package.magic = MAGIC;
	package.code = e;
	package.data_size = data.size();
	strcpy(package.data, data.c_str());

    if (package.code != 4) {
		std::cout << "------------J'ai Envoyé----------------" << std::endl;
		std::cout << package;
		std::cout << "---------------------------------------" << std::endl;
	}
	memcpy(buffTemp, &package, sizeof(package));
	return buffTemp;
}

const std::unordered_map<GUI::signal_e,
std::function<char *(ClientInfos_t, GUI::signal_e)>> CommandsFactory::_commands
{
	{GUI::signal_e::Elogin,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending packet of login to server" << std::endl;
		return createBuffer(e, infos.username + "\n" + infos.password + "\n");
	}},

	{GUI::signal_e::Elogout,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending packet of logout to server" << std::endl;
		return createBuffer(e, infos.username + "\n");
	}},

	{GUI::signal_e::Eregister,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending packet of register to server" << std::endl;
		return createBuffer(e, infos.username + "\n" + infos.password + "\n");
	}},

	{GUI::signal_e::Eaddcontact,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending packet of addContact to server" << std::endl;
		return createBuffer(e, infos.username + "\n");
	}},

	{GUI::signal_e::Erefuseincomingcall,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending packet of refuse incoming call to server" << std::endl;
		return createBuffer(e, infos.currentData + "\n");
	}},

	{GUI::signal_e::EcallX,
	[] (ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Telling server to call X" << std::endl;
		return createBuffer(e, infos.userToCall + "\n" + infos.myIp + "\n" + std::to_string(infos.audioPort) + "\n");
	}},

	{GUI::signal_e::Easkcontactlist,
	[](ClientInfos_t infos, GUI::signal_e e) {
		// std::cout << "Sending packet of ask contact list to server" << std::endl;
		return createBuffer(e, infos.username + "\n");
	}},
	{GUI::signal_e::EaskHistory,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending packet of ask history to server" << std::endl;
		return createBuffer(e, infos.currentData);
	}},

	{GUI::signal_e::EsendMsg,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending packet of sending Message to server" << std::endl;
		return createBuffer(e, infos.currentData);
	}},
	{GUI::signal_e::EAcceptIncomingCall,
	[](ClientInfos_t infos, GUI::signal_e e) {
		std::cout << "Sending accept call from " << infos.userToCall << " to server\n";
		return createBuffer(e, infos.userToCall + "\n" + infos.myIp + "\n" + std::to_string(infos.audioPort) + "\n");
	}},
};

char *CommandsFactory::callCommand(ClientInfos_t info, GUI::signal_e e)
{
    if (_commands.find(e) != _commands.end())
		return _commands.at(e)(info, e);
	return NULL;
}
