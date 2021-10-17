/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CallManager
*/

#include "CallManager.hpp"

using namespace Client::Managers;

CallManager::CallManager(const std::string &myIp, const unsigned short audioPort)
: QObject(), _myIp(myIp), _audioPort(audioPort)
{
    _udpClient = std::make_unique<Client::Network::UDPClient>();
    _soundManager = std::make_shared<PortAudioManager>();
    _encoderManager = std::make_shared<OpusManager>();
    _frameSize = _soundManager->getInputChannels() * sizeof(float);
    _inputBufferSize =  10 * _soundManager->getSampleRate() * _frameSize;
    _inputBuffer = new float[_inputBufferSize];
    _outputBuffer = new float[_inputBufferSize];
    _encoderManager->setBitRate(64000);
    _encoderManager->setSamplingRate(_soundManager->getSampleRate());
    _encoderManager->initDecoder();
    _encoderManager->initEncoder();
    _timer = new QTimer();
    _timer->setInterval(1);
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(sendAudioData()));
    // QObject::connect(_udpClient.get(), SIGNAL(getDataFromUDP()), this, SLOT(onReadAudioData()));
    // QObject::connect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

CallManager::~CallManager()
{
}

void CallManager::addPair(const std::string &ip, unsigned short port)
{
    _pairs[ip] = std::make_pair<unsigned short, std::time_t>((unsigned short)port, std::time_t(NULL));
}

unsigned char *CallManager::createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time)
{
    unsigned char *res = new unsigned char[buffSize * sizeof(unsigned char) + sizeof(std::time_t) + sizeof(int)];
    uintptr_t ptr = reinterpret_cast<uintptr_t >(res);

    std::memcpy((res), &time, sizeof(std::time_t));
    std::memcpy((res + sizeof(std::time_t)), &buffSize, sizeof(int));
    std::memcpy((res + sizeof(std::time_t) + sizeof(int)), compressedBuff, buffSize * sizeof(unsigned char));
    return res;
}

void CallManager::sendAudioData()
{
    Client::Network::packetUDP_t dataPacket;

    while (_soundManager->getBytesInInput() >= 480) {
        unsigned char *audioPacket;
        unsigned char *compressedBuffer = new unsigned char[_inputBufferSize];
        std::memset(compressedBuffer, 0, _inputBufferSize);
        _soundManager->retrieveInputBytes(_inputBuffer, 480);
        int compressedSize = _encoderManager->encode(compressedBuffer, _inputBuffer, 480, _inputBufferSize);
        audioPacket = createAudioPacket(compressedBuffer, compressedSize, std::time(nullptr));
        dataPacket.port = _audioPort;
        dataPacket.host = _myIp;
        dataPacket.data = audioPacket;
        for (auto &i : _pairs)
            _udpClient->send(dataPacket, i.first, i.second.first, compressedSize);

        delete [] compressedBuffer;
        delete [] audioPacket;
    }
    onReadAudioData();
}

void CallManager::onReadAudioData()
{
    Client::Network::packetUDP_t dataPacket;
    unsigned char *compressed;
    unsigned char *ptr;

    while (this->_udpClient->hasPendingDatagram()) {
        _udpClient->recieveDatagram();
    }
    while ((dataPacket = _udpClient->getData()).magicNum != 0) {
        if (dataPacket.magicNum == 0) {
            std::cout << "WRONG MAGIC NUMBER\n";
            return;
        }
        ptr = dataPacket.data;
        std::time_t timestamp;
        std::memcpy(&timestamp, ptr, sizeof(std::time_t));
        int buffSize;
        std::memcpy(&buffSize, (ptr + sizeof(std::time_t)), sizeof(int));
        compressed = new unsigned char[buffSize];
        std::memset(compressed, 0, buffSize);
        std::memcpy(compressed, (ptr + sizeof(std::time_t) + sizeof(buffSize)), buffSize * sizeof(unsigned char));
        auto outputBuffer = new float[_inputBufferSize];
        _encoderManager->decode(compressed, outputBuffer, 480, buffSize);
        _soundManager->feedBytesToOutput(outputBuffer, 480);
        delete [] outputBuffer;
    }
}

void CallManager::connectToHost()
{
    this->_udpClient->connectToHost(_myIp, _audioPort);
    this->_inCall = true;
    _timer->start();
}

void CallManager::beginCall()
{
    std::cout << "BEGIN CALL" << std::endl;
    std::cout << "Connect to client caller..." << _myIp << std::endl;
    this->connectToHost();
    // this->_soundManager->setOutputMute(false);
    // this->_soundManager->setMicMute(false);
    //TODO: set UP audio ????
}

void CallManager::endCall()
{
    this->_inCall = false;
    this->_udpClient->disconnect();
    _pairs.clear();

    //TODO: disable audio ????
    // this->_soundManager->setOutputMute(true);
    // this->_soundManager->setMicMute(true);
    QObject::disconnect(_timer, SIGNAL(timeout()), this, SLOT(sendAudioData()));
    QObject::disconnect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

#include "moc_CallManager.cpp"
