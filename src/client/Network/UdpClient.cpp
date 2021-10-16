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
        << QByteArray((const char *)packet.data, sizeof(packet.data))
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
    //QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

bool UDPClient::hasPendingDatagram()
{
    return _socket->hasPendingDatagrams();
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
    if (_socket->writeDatagram((const char *)packet.data, 13, receiverIp, port) == -1)
        std::cout << "Send fail to :" << ip  << ":" << port << std::endl;
}

packetUDP_t UDPClient::getData()
{
    QByteArray datagram;
    packetUDP_t new_packet;

    recieveDatagram();
    new_packet.magicNum = 0;
    if (!_data.empty()) {        
        new_packet = _data.front();
        _data.pop();
    }
    return new_packet;
}

void UDPClient::recieveDatagram()
{
    QHostAddress sender;
    QByteArray datagram;
    quint16 senderPort;
    packetUDP_t new_packet;
    char buffer[4096];

    int bytesRead = _socket->readDatagram(buffer, _socket->bytesAvailable(), &sender, &senderPort);
    if (bytesRead == -1) {
        std::cout << "Could not read datagram" << std::endl;
        return;
    }
    new_packet.host = sender.toString().toStdString();
    new_packet.port = senderPort;
    new_packet.data = new unsigned char[bytesRead];
    std::memcpy(new_packet.data, buffer, bytesRead);
    // for (int i = bytesRead - 1; i >= 0; i--) {
    //     new_packet.data.push_back(buffer[i]);
    //     std::cout << hex(buffer[i]);
    //     std::cout << " ";
    // }
    std::cout << std::endl;
    std::cout << "Received Message: " << (char *)buffer << std::endl;
    _data.push(new_packet);
}

void UDPClient::onReadyRead()
{
    QHostAddress sender;
    QByteArray datagram;
    quint16 senderPort;
    packetUDP_t new_packet;
    char buffer[4096];

    if (_socket->hasPendingDatagrams()) {
        int bytesRead = _socket->readDatagram(buffer, _socket->bytesAvailable(), &sender, &senderPort);
        if (bytesRead == -1) {
            std::cout << "Could not read datagram" << std::endl;
            return;
        }
        new_packet.host = sender.toString().toStdString();
        new_packet.port = senderPort;

        std::cout << "on ready read Message: " << (char *)new_packet.data << std::endl;
    } else {
        std::cout << "### ERRR: NO PENDING DATAGRAMS\n";
    }
    _data.push(new_packet);
}


void UDPClient::disconnect()
{
    _socket->disconnectFromHost();
}

#include "moc_UdpClient.cpp"
