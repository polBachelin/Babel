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
    QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void UDPClient::send(const packetUDP_t &packet, const std::string &ip, const unsigned short port)
{
    QByteArray buf;
    QHostAddress receiverIp;

    buf.append((const char *)packet.data);
    receiverIp.setAddress(QString::fromStdString(ip));
    std::cout << "Trying to send packet to host : " << packet.host  << " : " << packet.port << std::endl;
    _socket->writeDatagram(buf, receiverIp, port);
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