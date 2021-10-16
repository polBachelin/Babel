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

UDPClient::UDPClient() : _socket(nullptr)
{
}

UDPClient::~UDPClient()
{
}

void UDPClient::connectToHost(const std::string &ip)
{
    _socket = std::make_unique<QUdpSocket>();
    QHostAddress hostAddress;
    hostAddress.setAddress(QString::fromStdString(ip));
    _socket->bind(hostAddress, 6000);
    QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void UDPClient::send(const packetUDP_t &packet)
{
    //TODO: Faut pouvoir send à plusieurs UDP donc inclure le host et le port du receiver dans UDPPacket

    QByteArray buf;
    std::cout << "Trying to send packet to host : " << packet.host  << " : " << packet.port << std::endl;
    std::cout << "Packet size : " << packet.dataSize << std::endl;
    QHostAddress address;
    address.setAddress(QString::fromStdString(packet.host));
    buf.append((const char *)packet.data);
    _socket->writeDatagram(buf, address, packet.port);
}

packetUDP_t UDPClient::getData()
{
    packetUDP_t ret = _data.front();

    _data.pop();

    return ret;
}

void UDPClient::onReadyRead()
{
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    packetUDP_t new_packet;

    datagram.resize(_socket->pendingDatagramSize());
    QDataStream in(&datagram, QIODevice::ReadOnly);

    int bytesRead = _socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    if (bytesRead == -1) {
        std::cerr << "Could not read datagram" << std::endl;
        new_packet.host = "";
        new_packet.port = 0;
        new_packet.data = nullptr;
        new_packet.dataSize = 0;
        return;
    }
    std::cout << "[onReadyRead] bytesRead : " << bytesRead << std::endl;
    new_packet.host = sender.toString().toStdString();
    new_packet.port = senderPort;
    new_packet.data = (unsigned char *)datagram.data();
    new_packet.dataSize = bytesRead;

    qDebug() << "Message from: " << QString::fromStdString(new_packet.host);
    qDebug() << "Message port: " << QString::fromStdString(std::to_string(new_packet.port));
    qDebug() << "Message: " << QString::fromStdString(std::string((char *)new_packet.data));
    qDebug() << "Data Size: " << QString::fromStdString(std::to_string(new_packet.dataSize));
    
    _data.push(new_packet);
    emit getDataFromUDP();
}

void UDPClient::disconnect()
{
    _socket->disconnectFromHost();
}

#include "moc_UdpClient.cpp"