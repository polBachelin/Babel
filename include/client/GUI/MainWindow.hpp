/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** Mainwindow
*/

#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QtWidgets>
#include <memory>
#include "PageManager.hpp"
#include "TcpClient.hpp"

namespace Client {

    namespace GUI {

        class MainWindow : public QMainWindow
        {
            Q_OBJECT

            public:
                MainWindow();
                ~MainWindow();

            public slots:
                void changeCurrentPage(pageNames);
                void receivedSomething(QString msg);
                void gotError(QAbstractSocket::SocketError err);
                //void TryConnect

            private:
                void initConnections(void);
                PageManager _pages;
                Client::Network::TcpClient _tcpClient;
                ClientInfos _infos;

        };

    }
}

#endif /* !MAINWINDOW_HPP_ */
