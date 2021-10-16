/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** IUdpClient
*/

#ifndef IUDPCLIENT_HPP_
#define IUDPCLIENT_HPP_

#include <iostream>
#include <ctime>
#include <QtWidgets>
#include <vector>

namespace Client
{
    namespace Network
    {
        #pragma pack(1)
        typedef struct
        {
            // friend std::ostream &operator<<(std::ostream &out, const packetUDP_t &info)
            // {
            //     out << "\n---Infos UDP packet---\n"
            //     << "IpSender:" << info.host << "\n"
            //     << "PortSender:" << info.port << "\n"
            //     << "data:" << info.data.data() << "\n"
            //     << std::endl;
            //     return out;
            // }

            unsigned short magicNum = 987;
            std::vector<char> data;
            std::string host;
            unsigned short port;
            std::time_t timestamp;
        }  packetUDP_t;

        class IUDPClient
        {
            public:
                virtual packetUDP_t getData() = 0;
                virtual void disconnect() = 0;
                virtual void connectToHost(const std::string &ip, const unsigned short port) = 0;
                virtual void send(const packetUDP_t &packet, const std::string &ip, const unsigned short port) = 0;
        };
    }
}

Q_DECLARE_INTERFACE(Client::Network::IUDPClient, "Client::Network::IUDPClient")
#endif /* !IUDPCLIENT_HPP_ */
