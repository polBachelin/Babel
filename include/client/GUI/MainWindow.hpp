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

            signals:
                void validSignalResponse(QString, QString);
                void wrongSignalResponse(QString, QString);

            public slots:
                void checkSignal(ClientInfos, signal_e);
                void changeCurrentPage(pageNames);
                void receivedSomething(QString msg);
                void gotError(QAbstractSocket::SocketError err);
                //void TryConnect

            private:
                void initConnections(void);
                PageManager _pages;
                Client::Network::TcpClient _tcpClient;
                //TODO: intégrer les attributs suivants
                //Client::Network::PacketManager _packetManager;
                //Client::Network::UdpClient _udpClient;
                //std::shared_ptr<IEncodeManager> _encoderManager;
                //std::shared_ptr<ISoundManager> _soundManager;
                ClientInfos _infos;

        };

    }
}

#endif /* !MAINWINDOW_HPP_ */
