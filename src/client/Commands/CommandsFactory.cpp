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
		std::cout << "Sending packet of login to server\n";
		packet_t package;
		char *buffTemp = new char[sizeof(package)];

		package.magic = MAGIC;
		package.code = e;
		package.data_size = infos.username.size() + infos.password.size() + 2;
		std::string dataStr(infos.username + "\n" + infos.password + "\n");
		strcpy(package.data, dataStr.c_str());

		std::cout << "J'ai Envoyé ----------------------------" << std::endl;
    	std::cout << "Magic = " << package->magic << std::endl;
    	std::cout << "Code  = " << package->code << std::endl;
    	std::cout << "size  = " << package->data_size << std::endl;
    	std::cout << "data  = " << package->data << std::endl;
    	std::cout << "--------------------------------------" << std::endl;

		memcpy(buffTemp, &package, sizeof(package));
		return buffTemp;
	}},

	{GUI::signal_e::Eregister,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of register to server\n";
		packet_t package;
		char *buffTemp = new char[sizeof(package)];

		package.magic = MAGIC;
		package.code = e;
		package.data_size = infos.username.size() + infos.password.size() + 2;
		std::string dataStr(infos.username + "\n" + infos.password + "\n");
		strcpy(package.data, dataStr.c_str());

		std::cout << "J'ai Envoyé ----------------------------" << std::endl;
    	std::cout << "Magic = " << package->magic << std::endl;
    	std::cout << "Code  = " << package->code << std::endl;
    	std::cout << "size  = " << package->data_size << std::endl;
    	std::cout << "data  = " << package->data << std::endl;
    	std::cout << "--------------------------------------" << std::endl;

		memcpy(buffTemp, &package, sizeof(package));
		return buffTemp;
	}},

	{GUI::signal_e::Eaddcontact,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of addContact to server\n";
		packet_t package;
		char *buffTemp = new char[sizeof(package)];

		package.magic = MAGIC;
		package.code = e;
		package.data_size = infos.username.size() + 1;
		std::string dataStr(infos.username + "\n");
		strcpy(package.data, dataStr.c_str());

		std::cout << "J'ai Envoyé ----------------------------" << std::endl;
    	std::cout << "Magic = " << package->magic << std::endl;
    	std::cout << "Code  = " << package->code << std::endl;
    	std::cout << "size  = " << package->data_size << std::endl;
    	std::cout << "data  = " << package->data << std::endl;
    	std::cout << "--------------------------------------" << std::endl;

		memcpy(buffTemp, &package, sizeof(package));
		return buffTemp;
	}},

	{GUI::signal_e::Erefuseincomingcall,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of refuse incoming call to server\n";
		packet_t package;
		char *buffTemp = new char[sizeof(package)];

		package.magic = MAGIC;
		package.code = e;
		package.data_size = infos.username.size() + 1;
		std::string dataStr(infos.username + "\n");
		strcpy(package.data, dataStr.c_str());

		std::cout << "J'ai Envoyé ----------------------------" << std::endl;
    	std::cout << "Magic = " << package->magic << std::endl;
    	std::cout << "Code  = " << package->code << std::endl;
    	std::cout << "size  = " << package->data_size << std::endl;
    	std::cout << "data  = " << package->data << std::endl;
    	std::cout << "--------------------------------------" << std::endl;

		memcpy(buffTemp, &package, sizeof(package));
		return buffTemp;
	}},

	{GUI::signal_e::EcallX,
	[] (ClientInfos infos, GUI::signal_e e) {
		std::cout << "Telling server to call X\n";
		packet_t package;
		char *buffTemp = new char[sizeof(package)];

		package.magic = MAGIC;
		package.code = e;
		std::cout << infos.ip << std::endl;
		package.data_size = infos.userToCall.size() + infos.ip.size() + infos.port.size() + 3;
		std::string dataStr(infos.userToCall + "\n" + infos.ip + "\n" + infos.port + "\n");
		strcpy(package.data, dataStr.c_str());

		std::cout << "J'ai Envoyé ----------------------------" << std::endl;
    	std::cout << "Magic = " << package->magic << std::endl;
    	std::cout << "Code  = " << package->code << std::endl;
    	std::cout << "size  = " << package->data_size << std::endl;
    	std::cout << "data  = " << package->data << std::endl;
    	std::cout << "--------------------------------------" << std::endl;

		memcpy(buffTemp, &package, sizeof(package));
		return buffTemp;
	}},

	{GUI::signal_e::Easkcontactlist,
	[](ClientInfos infos, GUI::signal_e e) {
		std::cout << "Sending packet of register to server\n";
		packet_t package;
		char *buffTemp = new char[sizeof(package)];

		package.magic = MAGIC;
		package.code = e;
		package.data_size = infos.username.size() + 1;
		std::string dataStr(infos.username + "\n");
		strcpy(package.data, dataStr.c_str());

		std::cout << "J'ai Envoyé ----------------------------" << std::endl;
    	std::cout << "Magic = " << package->magic << std::endl;
    	std::cout << "Code  = " << package->code << std::endl;
    	std::cout << "size  = " << package->data_size << std::endl;
    	std::cout << "data  = " << package->data << std::endl;
    	std::cout << "--------------------------------------" << std::endl;

		memcpy(buffTemp, &package, sizeof(package));
		return buffTemp;
	}}
};

char *CommandsFactory::callCommand(ClientInfos info, GUI::signal_e e)
{
	return _commands.at(e)(info, e);
}
