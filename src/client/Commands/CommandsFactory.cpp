/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CommandsFactory
*/

#include "CommandsFactory.hpp"

using namespace Client;

const std::unordered_map<GUI::signal_e, 
std::function<int(ClientInfos, GUI::signal_e)>> CommandsFactory::_commands 
{
	{GUI::signal_e::Elogin,
	[](ClientInfos, GUI::signal_e) {
		std::cout << "Sending packet of logiin to server\n";
		return 1;
	}}
};

void CommandsFactory::callCommand(ClientInfos info, GUI::signal_e e)
{
	_commands.at(e)(info, e);
}