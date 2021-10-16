/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** BabelClient
*/

#ifndef BABELCLIENT_HPP_
#define BABELCLIENT_HPP_


#include <QApplication>
#include "PageManager.hpp"
#include "MainWindow.hpp"
#include <iostream>
#include "TcpClient.hpp"


namespace Client {
class BabelClient : public QApplication
{

    public:
        BabelClient(int &argc, char **argv);
        ~BabelClient();
        int start();


    private:
        std::unique_ptr<Client::GUI::MainWindow> _mainWindow;
};

}

#endif /* !BABELCLIENT_HPP_ */
