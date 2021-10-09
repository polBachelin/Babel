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
        << QByteArray(packet.data, sizeof(packet.data))
        << (qint16)packet.port;
    return out;
}

UDPClient::UDPClient() : _socket(nullptr)
{
}

UDPClient::~UDPClient()
{
}

void UDPClient::connectToPair()
{
    _socket = std::make_unique<QUdpSocket>();
    _socket->bind(QHostAddress::LocalHost, 5000);
    QObject::connect(_socket.get(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    send((packetUDP_t){"Hello pto", "localhost", 5000});
}

void UDPClient::send(const packetUDP_t &packet)
{
    //TODO: Faut pouvoir send à plusieurs UDP donc inclure le host et le port du receiver dans UDPPacket

    QByteArray buf;
    std::cout << "Trying to send packe to host : " << packet.host  << " : " << packet.port << std::endl;
    //QDataStream s(&buf, QIODevice::WriteOnly);
    // The encoding is big endian by default, on all systems. You
    // can change it if you wish.
    //if (false) s.setByteOrder(QDataStream::LittleEndian);
    //s << (QString)packet.data << QString::fromStdString(packet.host) << (qint16)packet.port;
    buf.append(packet.data);
    _socket->writeDatagram(buf, QHostAddress::LocalHost, packet.port);
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

    _socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

    new_packet.host = sender.toString().toStdString();
    new_packet.port = senderPort;
    new_packet.data = datagram.data();

    qDebug() << "Message from: " << QString::fromStdString(new_packet.host);
    qDebug() << "Message port: " << QString::fromStdString(std::to_string(new_packet.port));
    qDebug() << "Message: " << QString::fromStdString(std::string(new_packet.data));

    _data.push(new_packet);
}

void UDPClient::disconnect()
{
    _socket->disconnectFromHost();
}

#include "moc_UdpClient.cpp"