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

namespace Client
{
    namespace Network
    {
        #pragma pack(push, 1)
        typedef struct audioPacket
        {
            unsigned short magicNum;
            unsigned char *data;
            unsigned short sizeOfData;
            std::time_t timestamp;
        } audioPacket_t;
        #pragma pack(pop)

        typedef struct packetUDP
        {
            char *data;
            std::string host;
            unsigned short port;
        } packetUDP_t;

        class IUDPClient
        {
            public:
                virtual void connectToPair() = 0;
                virtual packetUDP_t getData() = 0;
                virtual void disconnect() = 0;
                virtual void send(const packetUDP_t &packet) = 0;

        };
    }
}

Q_DECLARE_INTERFACE(Client::Network::IUDPClient, "Client::Network::IUDPClient")
#endif /* !IUDPCLIENT_HPP_ */
