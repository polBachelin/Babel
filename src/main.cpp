/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include <iostream>
#include "ISoundManager.hpp"
#include "IEncodeManager.hpp"
#include "ITcpServer.hpp"
#include "DLLoader.hpp"
#include "ConfigFileParser.hpp"
#include "Error.hpp"
#include <unordered_map>

#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)

int main(void)
{
    std::unordered_map<ConfigFileParser::LIB_TYPE, std::vector<std::string>> _libs = ConfigFileParser::parseFile();

    std::shared_ptr<ITcpServer> serv = DLLoader<ITcpServer>::getEntryPoint(_libs[ConfigFileParser::LIB_TYPE::NETWORK].front());

    if (serv) {
        serv->initServer(5000);
        serv->startAccept();
    }
    return 0;
}