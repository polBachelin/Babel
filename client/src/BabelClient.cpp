/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** BabelClient
*/

#include "BabelClient.hpp"

using namespace Client;

BabelClient::BabelClient(int &argc, char **argv) : QApplication(argc, argv)
{
}

BabelClient::~BabelClient()
{

    std::cout << "BabelClient détruit" << std::endl;

}


int BabelClient::start()
{
    mainWindow.show();

    return this->exec();
}
