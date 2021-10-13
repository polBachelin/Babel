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

                void signalReceivedLoader();

            signals:
                void validSignInResponse(ClientInfos);
                void wrongSignInResponse(ClientInfos);
                void validRegisterResponse(ClientInfos);
                void wrongRegisterResponse(ClientInfos);
                void contactAddSuccess(ClientInfos);
                void contactAddFailed(ClientInfos);
                void incomingCall(ClientInfos);
                void contactList(ClientInfos);
                void invitationContactReceived(ClientInfos);
                void callRefused(ClientInfos);

            public slots:
                void checkSignal(ClientInfos, signal_e);
                void changeCurrentPage(pageNames, ClientInfos);
                void receivedSomething(QByteArray);
                void onStartCallConnection(ClientInfos);
                void gotError(QAbstractSocket::SocketError err);
                //void TryConnect

            private:
                void initConnections(void);
                PageManager _pages;
                Network::TcpClient _tcpClient;
                ClientInfos _infos;
                std::unordered_map<int, std::function<void(ClientInfos)>> _signalPageMap;

       };

    }
}

#endif /* !MAINWINDOW_HPP_ */
