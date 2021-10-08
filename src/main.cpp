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
#include "asio.hpp"
#include "PortAudioManager.hpp"
#include "AsioTcpServer.hpp"
#define SAMPLE_RATE  (44100)
#define FRAMES_PER_BUFFER (512)
#define NUM_SECONDS     (5)

int main(int ac, char **av)
{
   //std::unordered_map<ConfigFileParser::LIB_TYPE, std::vector<std::string>> _libs = ConfigFileParser::parseFile();

    //std::shared_ptr<ITcpServer> serv = DLLoader<ITcpServer>::getEntryPoint(_libs[ConfigFileParser::LIB_TYPE::NETWORK].front());
    std::shared_ptr<AsioTcpServer> serv = std::make_shared<AsioTcpServer>();

    if (serv) {
        if (ac == 1) {
            std::cout << "Port : 5000" << std::endl;
            serv->initServer(5000);
        } else {
            std::cout << "Port : " << av[1] << std::endl;
            serv->initServer(std::atoi(av[1]));
        }
        serv->startAccept();
    }
    return 0;
}