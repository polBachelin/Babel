/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CommandParser
*/

#ifndef COMMANDPARSER_HPP_
#define COMMANDPARSER_HPP_

#include <unordered_map>
#include <memory>
#include <functional>
#include "ICommand.hpp"

typedef std::size_t CommandCode;

namespace Client
{
    namespace Commands
    {
        class CommandParser
        {
            public:
                CommandParser();
                ~CommandParser();

            private:
                const std::unordered_map<CommandCode, std::function<std::unique_ptr<Commands::ICommand>>()>>
        };
    }

}

#endif /* !COMMANDPARSER_HPP_ */
