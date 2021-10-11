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
#include "CommandsFactory.hpp"
#include "TcpClient.hpp"
#include "UdpClient.hpp"
#include "CallManager.hpp"

namespace Client {


    namespace GUI {

        class MainWindow : public QMainWindow
        {
            Q_OBJECT

            public:
                MainWindow(const QString hostAddress,
                            int portVal);
                ~MainWindow();

            signals:
                void validSignalResponse(Client::ClientInfos);
                void wrongSignalResponse(Client::ClientInfos);

            public slots:
                void checkSignal(ClientInfos, signal_e);
                void changeCurrentPage(pageNames);
                void receivedSomething(QByteArray);
                void gotError(QAbstractSocket::SocketError err);
                //void TryConnect

            private:
                void initConnections(void);
                PageManager _pages;
                Client::Network::TcpClient _tcpClient;
                //TODO: remove this after audio;
                Client::Managers::CallManager _callManager;
                ClientInfos _infos;

                std::unordered_map<int, std::function<void(Client::ClientInfos)>> _signalPageMap;

       };

    }
}

#endif /* !MAINWINDOW_HPP_ */
