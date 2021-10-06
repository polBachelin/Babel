/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CallManager
*/

#include "CallManager.hpp"

using namespace Client::Managers;

CallManager::CallManager() : QObject()
{
    _udpClient = std::make_unique<Client::Network::UDPClient>();
    _udpClient->connectToPair();
    //connect(_soundManager, inputAvailable, this, sendAudioData);
    //connect(_soundManager, outputAvailable, this, onReadAudioData);
}

CallManager::~CallManager()
{
}

void CallManager::sendAudioData()
{
    Client::Network::packetUDP_t dataPacket;
    Client::Network::audioPacket_t audioPacket = {};
    char *ptr;

    audioPacket.timestamp = std::time(nullptr);

    // ? audioPacket.data = ??????
    unsigned char toto[512] = "wsh";
    audioPacket.data = toto;
    audioPacket.sizeOfData = 3;
    ptr = reinterpret_cast<char *>(&audioPacket);

    dataPacket.port = _audioPort;
    dataPacket.data = ptr;
    for (auto &pair : _pairs) {
        dataPacket.host = pair.first;
        _udpClient->send(dataPacket);
    }
}//TODO: paramètre input compressé

void CallManager::onReadAudioData()
{
    // TODO:: créer un compressedBuffer;
    Client::Network::packetUDP_t dataPacket = this->_udpClient->getData();
    auto *audioPacket = reinterpret_cast<Client::Network::audioPacket_t *>(dataPacket.data);

    if (audioPacket->magicNum != _magicNum) {
        std::cerr << "OVNI" << std::endl;
        return;
    }
    // ? changer la condition pour checker le timestamp
    if (audioPacket->timestamp < _pairs[dataPacket.host])
        return;
    _pairs[dataPacket.host] = audioPacket->timestamp;
    //this->interpretSound(compressedBuffer, dataPacket.host)
}

void CallManager::beginCall(const std::vector<std::string> &pairs)
{
    this->_inCall = true;
    this->_udpClient->connectToPair();
    for(auto &pair : pairs)
        _pairs.emplace(pair, 0);
}

void CallManager::endCall()
{
    this->_inCall = false;
    this->_udpClient->disconnect();
}

#include "moc_CallManager.cpp"