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
    std::cout << "Trying to send packet to host : " << packet.host  << " : " << packet.port << std::endl;
    std::cout << "Packet size : " << packet.dataSize << std::endl;
    QHostAddress receiverIp;

    std::cout << "data size == " << strlen((const char *)packet.data) << std::endl;
    buf.append((const char *)packet.data);
    receiverIp.setAddress(QString::fromStdString(ip));
    std::cout << "Trying to send packet to : " << ip  << " : " << port << std::endl;
    std::cout << "Packet buf size == " << buf.size() << std::endl;
    if (_socket->writeDatagram(buf, receiverIp, port) == -1)
        std::cout << "Send fail to :" << ip  << ":" << port << std::endl;
}

packetUDP_t UDPClient::getData()
{
    QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    packetUDP_t new_packet;
    QNetworkDatagram datagramNetwork = _data.front();


    _data.pop();
    datagram = datagramNetwork.data();
    int bytesRead = _socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
    if (bytesRead == -1) {
        std::cerr << "Could not read datagram" << std::endl;
        new_packet.dataSize = -1;
        return new_packet;
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
    return new_packet;
}

void UDPClient::onReadyRead()
{
    QHostAddress sender;
    QByteArray datagram;
    quint16 senderPort;
    packetUDP_t new_packet;

    std::cout << "SOCKET BYTES AVAILBALE : " << _socket->bytesAvailable() << std::endl;
    // if (_socket->hasPendingDatagrams()) {
    //     datagram.resize(_socket->bytesAvailable());
    //     int bytesRead = _socket->readDatagram(datagram.data(), 9, &sender, &senderPort);
    //     if (bytesRead == -1) {
    //         std::cout << "Could not read datagram" << std::endl;
    //         emit getDataFromUDP();
    //         return;
    //     }
    //     new_packet.host = sender.toString().toStdString();
    //     new_packet.port = senderPort;
    //     new_packet.data = (unsigned char *)datagram.data();
    //     new_packet.dataSize = bytesRead;
    //     std::cout << "Message: " << QString::fromStdString(std::string((char *)new_packet.data)).toStdString() << std::endl;
    // } else {
    //     std::cout << "### ERRR: NO PENDING DATAGRAMS\n";
    while (_socket->hasPendingDatagrams())
    {
        _data.push(_socket->receiveDatagram());
        emit getDataFromUDP();
    }
}


void UDPClient::disconnect()
{
    _socket->disconnectFromHost();
}

#include "moc_UdpClient.cpp"
