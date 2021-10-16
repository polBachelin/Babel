/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** UdpClient
*/

#include "UdpClient.hpp"

using namespace Client::Network;

QDataStream& operator <<(QDataStream& out,packetUDP_t &packet)
{
    out << QString::fromStdString(packet.host)
        << QByteArray((const char *)packet.data.data(), sizeof(packet.data))
        << (qint16)packet.port;
    return out;
}

UDPClient::UDPClient()
{
    _socket = std::make_unique<QUdpSocket>();
}

UDPClient::~UDPClient()
{
}

void UDPClient::connectToHost(const std::string &ip, const unsigned short port)
{
    QHostAddress hostAddress;

    hostAddress.setAddress(QString::fromStdString(ip));
    _socket->bind(hostAddress, port);
    QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void UDPClient::send(const packetUDP_t &packet, const std::string &ip, const unsigned short port)
{
    QByteArray buf;
    //std::cout << "Trying to send packet to host : " << packet.host  << " : " << packet.port << std::endl;
    QHostAddress receiverIp;

    //buf.append((const char *)packet.data);
    receiverIp.setAddress(QString::fromStdString(ip));
    //std::cout << "Trying to send packet to : " << ip  << " : " << port << std::endl;
    //std::cout << "PACKET DATA SIZE : " << packet.data.size() << std::endl;
    if (_socket->writeDatagram(packet.data.data(), packet.data.size(), receiverIp, port) == -1)
        std::cout << "Send fail to :" << ip  << ":" << port << std::endl;
}

packetUDP_t UDPClient::getData()
{
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    packetUDP_t new_packet;

    new_packet.magicNum = -1;
    if (!_data.empty()) {        
        new_packet = _data.front();
        _data.pop();
    }
    return new_packet;
}

void UDPClient::onReadyRead()
{
    QHostAddress sender;
    QByteArray datagram;
    quint16 senderPort;
    packetUDP_t new_packet;

    //std::cout << "SOCKET BYTES AVAILBALE : " << _socket->bytesAvailable() << std::endl;
    if (_socket->hasPendingDatagrams()) {
        datagram.resize(_socket->bytesAvailable());
        int bytesRead = _socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        if (bytesRead == -1) {
            std::cout << "Could not read datagram" << std::endl;
            emit getDataFromUDP();
            return;
        }
        new_packet.host = sender.toString().toStdString();
        new_packet.port = senderPort;
        for (int i = 0; datagram.data()[i]; i++) {
            new_packet.data.push_back(datagram.data()[i]);
        }
        std::cout << "Received Message: " << (char *)new_packet.data.data() << std::endl;
    } else {
        std::cout << "### ERRR: NO PENDING DATAGRAMS\n";
    }
    _data.push(new_packet);
    emit getDataFromUDP();
}


void UDPClient::disconnect()
{
    _socket->disconnectFromHost();
}

#include "moc_UdpClient.cpp"
