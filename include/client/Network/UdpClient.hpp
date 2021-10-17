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
#include <QNetworkDatagram>
#include <queue>

namespace Client
{
    namespace Network
    {

        struct HexCharStruct
        {
            char c;
            HexCharStruct(char _c) : c(_c) { }
        };

        inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
        {
            return (o << std::hex << (int)hs.c);
        }

        inline HexCharStruct hex(char _c)
        {
            return HexCharStruct(_c);
        }

        class UDPClient : public QObject,  public IUDPClient
        {
            Q_OBJECT
            Q_INTERFACES(Client::Network::IUDPClient)

            public:
                UDPClient();
                ~UDPClient();
                void connectToHost(const std::string &myIp, const unsigned short port) override;
                void send(const packetUDP_t &packet, const std::string &ip, const unsigned short port, const int &size) override;
                void disconnect() override;
                packetUDP_t getData() override;
                int getNbData();
                bool hasPendingDatagram() override;
                void recieveDatagram();
            signals:
                void getDataFromUDP();

            private slots:
                void onReadyRead();

            private:
                std::unique_ptr<QUdpSocket> _socket;
                std::queue<packetUDP_t> _data;
        };
    }
}


#endif /* !UDPCLIENT_HPP_ */
