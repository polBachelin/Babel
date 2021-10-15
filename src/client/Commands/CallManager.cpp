/*
** EPITECH PROJECT, 2021
** B-CPP-500-REN-5-1-babel-killian.vallette
** File description:
** CallManager
*/

#include "CallManager.hpp"

using namespace Client::Managers;

CallManager::CallManager(const std::string &myIp) : QObject(), _ip(myIp)
{
    _udpClient = std::make_unique<Client::Network::UDPClient>();
    _soundManager = std::make_shared<PortAudioManager>();
    _encoderManager = std::make_shared<OpusManager>();
    _frameSize = _soundManager->getInputChannels() * sizeof(float);
    _inputBufferSize =  3 * _soundManager->getSampleRate() * _frameSize;
    _inputBuffer = new float[_inputBufferSize];
    _outputBuffer = new float[_inputBufferSize];
    _encoderManager->setBitRate(10);
    _encoderManager->setSamplingRate(_soundManager->getSampleRate());
    _encoderManager->initDecoder();
    _encoderManager->initEncoder();
    _soundManager->startInputStream();
    _soundManager->startOutputStream();
    //TODO: connect input to sendAudio + output to readAudio
    QObject::connect(_udpClient.get(), SIGNAL(getDataFromUDP()), this, SLOT(onReadAudioData()));
    QObject::connect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

CallManager::~CallManager()
{
}

unsigned char *CallManager::createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time)
{
    unsigned char *res = new unsigned char[buffSize + sizeof(time) + sizeof(unsigned char) + sizeof(int)];
    uintptr_t ptr = reinterpret_cast<uintptr_t >(res);
    uint32_t networkBuffSize = htonl(buffSize);
    uint32_t networkTime = htonl(time);

    std::memcpy((void *)ptr, &networkTime, sizeof(time));
    ptr += sizeof(time);
    std::memcpy((void *)ptr, &networkBuffSize, sizeof(buffSize));
    ptr += sizeof(buffSize);
    std::memcpy((void *)ptr, compressedBuff, buffSize * sizeof(compressedBuff));
    return res;
}

void CallManager::sendAudioData()
{
    Client::Network::packetUDP_t dataPacket;
    unsigned char *audioPacket;
    unsigned char *compressedBuffer = new unsigned char[_inputBufferSize];

    std::memset(compressedBuffer, 0, _inputBufferSize);
    _soundManager->retrieveInputBytes(_inputBuffer, 480);
    int compressedSize = _encoderManager->encode(compressedBuffer, _inputBuffer, 480, _inputBufferSize);
    audioPacket = createAudioPacket(compressedBuffer, compressedSize, std::time(nullptr));

    dataPacket.port = _audioPort;
    dataPacket.data = audioPacket;
    dataPacket.host = _contactIp;

    std::cout <<  "Infos from Caller: " << std::to_string(dataPacket.port) << ":" << compressedSize << std::endl;
    _udpClient->send(dataPacket);

    delete [] compressedBuffer;
    delete [] audioPacket;
}

void CallManager::onReadAudioData()
{

    Client::Network::packetUDP_t dataPacket = this->_udpClient->getData();
    unsigned char *compressed;
    uintptr_t ptr = reinterpret_cast<uintptr_t>(dataPacket.data);

    // ? changer la condition pour checker le timestamp
    //if (audioPacket->timestamp < _pairs[dataPacket.host])
        //return;
    std::time_t *timestampPtr = reinterpret_cast<std::time_t *>(ptr);
    ptr += sizeof(std::time_t);
    int *buffSizePtr = reinterpret_cast<int *>(ptr);
    std::time_t timestamp = ntohl(*timestampPtr);
    (void)timestamp;
    int buffSize = ntohl(*buffSizePtr);
    compressed = new unsigned char[buffSize];
    std::memcpy(compressed, (void *)(ptr + sizeof(std::time_t) + sizeof(buffSize)), buffSize * sizeof(compressed));
    _encoderManager->decode(compressed, _outputBuffer, 480, buffSize);
    _soundManager->feedBytesToOutput(_outputBuffer, 480);
}

void CallManager::connectToHost(const std::string &ip)
{
    std::cout << "CONNECT TO HOST WITH IP : " << ip << std::endl;
    this->_udpClient->connectToHost(ip);
    _contactIp = ip;
    this->_inCall = true;
    this->sendAudioData();
}

void CallManager::beginCall()
{
    std::cout << "BEGIN CALL" << std::endl;
    std::cout << "Connect to client caller..." << _ip << std::endl;
    this->connectToHost(_ip);
    std::cout << "Send data OK..." << std::endl;
}

void CallManager::endCall()
{
    this->_inCall = false;
    this->_udpClient->disconnect();
    QObject::disconnect(this, SIGNAL(sendData()), this, SLOT(sendAudioData));
}

#include "moc_CallManager.cpp"