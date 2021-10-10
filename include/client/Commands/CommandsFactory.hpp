/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** CommandsFactory
*/

#ifndef COMMANDSFACTORY_HPP_
#define COMMANDSFACTORY_HPP_

#include "structs.hpp"
#include "APage.hpp"
#include <functional>
#include <unordered_map>

namespace Client {
	class CommandsFactory {
		public:
			CommandsFactory() = default;
			~CommandsFactory() = default;

			static char *callCommand(ClientInfos, GUI::signal_e);
		private:
			static const std::unordered_map<GUI::signal_e, std::function<char *(ClientInfos, GUI::signal_e)>> _commands;
	};
}

#endif /* !COMMANDSFACTORY_HPP_ */
