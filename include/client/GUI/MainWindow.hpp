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
                            int portVal, int audioPort);
                ~MainWindow();

                void signalReceivedLoader();

            signals:
                void validSignInResponse(ClientInfos_t);
                void wrongSignInResponse(ClientInfos_t);
                void validRegisterResponse(ClientInfos_t);
                void wrongRegisterResponse(ClientInfos_t);
                void contactAddSuccess(ClientInfos_t);
                void contactAddFailed(ClientInfos_t);
                void incomingCall(ClientInfos_t);
                void contactList(ClientInfos_t);
                void invitationContactReceived(ClientInfos_t);
                void callRefused(ClientInfos_t);
                void receivedMessage(ClientInfos_t);

            public slots:
                void checkSignal(ClientInfos_t, signal_e);
                void changeCurrentPage(pageNames, ClientInfos_t);
                void receivedSomething(QByteArray);
                void gotError(QAbstractSocket::SocketError err);
                //void TryConnect

            private:
                void initConnections(void);

                std::unique_ptr<PageManager> _pages;
                Network::TcpClient _tcpClient;
                ClientInfos_t _infos;
                std::unordered_map<receivedSignal_e, std::function<void(ClientInfos_t)>> _signalPageMap;
        };

    }
}

#endif /* !MAINWINDOW_HPP_ */
