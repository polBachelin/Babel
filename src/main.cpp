/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include <iostream>
#include "ISoundManager.hpp"
#include "DLLoader.hpp"
#include "ConfigFileParser.hpp"
#include <unordered_map>

int main(void)
{
    std::unordered_map<ConfigFileParser::LIB_TYPE, std::vector<std::string>> _libs = ConfigFileParser::parseFile();

    std::cout << _libs[ConfigFileParser::LIB_TYPE::SOUND].front() << std::endl;
    std::shared_ptr<ISoundManager> ptr = DLLoader<ISoundManager>::getEntryPoint(_libs[ConfigFileParser::LIB_TYPE::SOUND].front());
    
    if (ptr) {
        ptr->recordAudio();
        ptr->playAudio();
    }
    return 0;
}