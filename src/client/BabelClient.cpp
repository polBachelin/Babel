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
    QString hostAddress = "192.168.0.17";
    int portVal = 5000;

    if (argc == 3) {
        hostAddress = argv[1];
        portVal = std::atoi(argv[2]);
    }
    std::cout << hostAddress.toStdString() << " | " << portVal << std::endl;
    _mainWindow = std::make_unique<Client::GUI::MainWindow>(hostAddress, portVal);
}

BabelClient::~BabelClient()
{
    std::cout << "BabelClient détruit" << std::endl;
}

int BabelClient::start()
{
    _mainWindow->show();

    return this->exec();
}
