/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** BabelClient
*/

#include "BabelClient.hpp"

using namespace Client;

static bool checkPort(std::string port)
{
    int valid = 0;

    for (auto c : port)
        if (!(valid = std::isdigit(c)))
            return false;
    return true;
}

BabelClient::BabelClient(int &argc, char **argv) : QApplication(argc, argv)
{
    QString hostAddress = "0.0.0.0";
    int portVal = 0;

    if (argc == 3 && checkPort((std::string)argv[2])) {
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
