/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** UdpClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "IUdpClient.hpp"
#include <QtCore/QObject>
#include <memory>
#include <QUdpSocket>
#include <queue>

namespace Client
{
    namespace Network
    {
        class UDPClient : public QObject,  public IUDPClient
        {
            Q_OBJECT
            Q_INTERFACES(Client::Network::IUDPClient)

            public:
                UDPClient();
                ~UDPClient();
                void connectToPair() override;
                void send(const packetUDP_t &packet) override;
                void disconnect() override;
                packetUDP_t getData() override;

            private slots:
                void onReadyRead();

            private:
                std::unique_ptr<QUdpSocket> _socket;
                std::queue<packetUDP_t> _data;
        };
    }
}


#endif /* !UDPCLIENT_HPP_ */
