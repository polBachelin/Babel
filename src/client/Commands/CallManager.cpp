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
    _soundManager = std::make_shared<PortAudioManager>();
    _encoderManager = std::make_shared<OpusManager>();
    _frameSize = _soundManager->getInputChannels() * sizeof(float);
    _inputBufferSize =  3 * _soundManager->getSampleRate() * _frameSize;
    _inputBuffer = new float[_inputBufferSize];
    _outputBuffer = new float[_inputBufferSize];
    _udpClient->connectToPair();
    //connect(_soundManager, inputAvailable, this, sendAudioData);
    //connect(_soundManager, outputAvailable, this, onReadAudioData);
}

CallManager::~CallManager()
{
}

Client::Network::audioPacket_t CallManager::createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time)
{
    Client::Network::audioPacket_t audioPacket;

    audioPacket.timestamp = time;
    audioPacket.data = new unsigned char[buffSize];
    std::memcpy(audioPacket.data, compressedBuff, buffSize);
    audioPacket.sizeOfData = buffSize;
    return audioPacket;
}

void CallManager::sendAudioData()
{
    Client::Network::packetUDP_t dataPacket;
    Client::Network::audioPacket_t audioPacket;
    char *ptr;

    unsigned char *compressedBuffer = new unsigned char[_inputBufferSize];
    std::memset(compressedBuffer, 0, _inputBufferSize);
    _soundManager->retrieveInputBytes(_inputBuffer, 512);
    int compressedSize = _encoderManager->encode(compressedBuffer, _inputBuffer, 512, _inputBufferSize);
    audioPacket = createAudioPacket(compressedBuffer, compressedSize, std::time(nullptr));    
    ptr = reinterpret_cast<char *>(&audioPacket);
    dataPacket.port = _audioPort;
    dataPacket.data = ptr;
    for (auto &pair : _pairs) {
        dataPacket.host = pair.first;
        _udpClient->send(dataPacket);
    }
    delete [] compressedBuffer;
    delete [] audioPacket.data;
}//TODO: paramètre input compressé

void CallManager::onReadAudioData()
{
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
    _encoderManager->decode(audioPacket->data, _outputBuffer, 512, audioPacket->sizeOfData);
    _soundManager->feedBytesToOutput(_outputBuffer, 512);
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