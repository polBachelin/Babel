/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CommandsFactory
*/

#include "CommandsFactory.hpp"

using namespace Client;

const std::unordered_map<GUI::signal_e, 
std::function<char *(ClientInfos, GUI::signal_e)>> CommandsFactory::_commands 
{
	{GUI::signal_e::Elogin,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of logiin to server\n";
		packet_t package;
		char *buffTemp = new char[sizeof(package)];
		
		package.magic = MAGIC;
		package.code = e;
		package.data_size = infos.username.size() + infos.password.size() + 2;
		std::string dataStr(infos.username + "\n" + infos.password + "\n");
		strcpy(package.data, dataStr.c_str());
		memcpy(buffTemp, &package, sizeof(package));
		return buffTemp;
	}},

	{GUI::signal_e::EcallX,
	[] (ClientInfos infos, GUI::signal_e e) {
		std::cout << "Telling server to call X\n";
		return nullptr;
	}}
};

char *CommandsFactory::callCommand(ClientInfos info, GUI::signal_e e)
{
	return _commands.at(e)(info, e);
}