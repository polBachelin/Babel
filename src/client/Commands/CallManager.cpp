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
    _inputBufferSize =  3 * _soundManager->getSampleRate() * _frameSize;
    _inputBuffer = new float[_inputBufferSize];
    _outputBuffer = new float[_inputBufferSize];
    _encoderManager->setBitRate(10);
    _encoderManager->setSamplingRate(_soundManager->getSampleRate());
    _encoderManager->initDecoder();
    _encoderManager->initEncoder();
    _soundManager->startInputStream();
    _soundManager->startOutputStream();
    QObject::connect(_udpClient.get(), SIGNAL(getDataFromUDP()), this, SLOT(onReadAudioData()));
    QObject::connect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

CallManager::~CallManager()
{
}

void CallManager::addPair(const std::string &ip, unsigned short port)
{
    std::cout << "Add Pair: " << ip << ":" << port << std::endl;
    _pairs[ip] = std::make_pair<unsigned short, std::time_t>((unsigned short)port, std::time_t(NULL));
}

unsigned char *CallManager::createAudioPacket(unsigned char *compressedBuff, int buffSize, std::time_t time)
{
    unsigned char *res = new unsigned char[buffSize * sizeof(unsigned char) + sizeof(std::time_t) + sizeof(int)];
    std::cout << "SIZE OF BUFFER === " << buffSize *sizeof(unsigned char) + sizeof(std::time_t) + sizeof(int) << std::endl;
    uintptr_t ptr = reinterpret_cast<uintptr_t >(res);
    // uint32_t networkBuffSize = htonl(buffSize);
    // uint32_t networkTime = htonl(time);

    //std::cout << "[createAudioPacket] buffSize : " << buffSize << std::endl;
    std::cout << "[createAudioPacket] networkBuffSize : " << buffSize << std::endl;
    std::cout << "[createAudioPacket] networkTime : " << time << std::endl;

    std::memcpy(reinterpret_cast<void *>(ptr), &time, sizeof(std::time_t));
    std::memcpy(reinterpret_cast<void *>(ptr + sizeof(std::time_t)), &buffSize, sizeof(int));
    std::memcpy(reinterpret_cast<void *>(ptr + sizeof(std::time_t) + sizeof(int)), compressedBuff, buffSize * sizeof(unsigned char));
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
    dataPacket.host = _myIp;
    dataPacket.data = audioPacket;
    dataPacket.dataSize = compressedSize;

    std::cout << "-----SENDING AUDIO DATA----\n";
    //std::cout << "BuffSize : " << compressedSize << std::endl;
    std::cout << "data size == " << strlen((const char *)audioPacket) << std::endl;
    std::cout << "Message: " << QString::fromStdString(std::string((char *)dataPacket.data)).toStdString() << std::endl;
    int *ptrBuffSize = reinterpret_cast<int *>(dataPacket.data + sizeof(std::time_t));
    std::cout << "Checking data Packet networkBuffSize should be same as [createAudioPacket] one :  " << *ptrBuffSize << std::endl;
    std::cout << "---------------------------\n"; 
    //std::cout <<  "Infos from Caller: " << std::to_string(dataPacket.port) << std::endl;

    for (auto &i : _pairs)
        _udpClient->send(dataPacket, i.first, i.second.first);

    delete [] compressedBuffer;
    delete [] audioPacket;
}

void CallManager::onReadAudioData()
{
    Client::Network::packetUDP_t dataPacket = this->_udpClient->getData();
    if (dataPacket.dataSize == -1)
        return;
    unsigned char *compressed = nullptr;
    uintptr_t ptr = reinterpret_cast<uintptr_t>(dataPacket.data);

    std::time_t *timestampPtr = reinterpret_cast<std::time_t *>(ptr);
    int *buffSizePtr = reinterpret_cast<int *>(ptr + sizeof(std::time_t));
    std::cout << dataPacket << std::endl;
    std::cout << "-----READING AUDIO DATA----\n";
    std::cout << "Network Time : " << *timestampPtr << std::endl;
    std::cout << "Network BuffSize : " << *buffSizePtr << std::endl;
    std::cout << "---------------------------\n";

    addPair(dataPacket.host, dataPacket.port);
    //compressed = new unsigned char[buffSize];
    //std::memcpy(compressed, (void *)(ptr + sizeof(std::time_t) + sizeof(buffSize)), buffSize * sizeof(compressed));

    // _encoderManager->decode(compressed, _outputBuffer, 480, buffSize);
    // _soundManager->feedBytesToOutput(_outputBuffer, 480);
    emit sendData();
}

void CallManager::connectToHost()
{
    std::cout << "UDP bind my IP : " << _myIp << std::endl;
    this->_udpClient->connectToHost(_myIp, _audioPort);
    this->_inCall = true;
    this->sendAudioData();
}

void CallManager::beginCall()
{
    std::cout << "BEGIN CALL" << std::endl;
    std::cout << "Connect to client caller..." << _myIp << std::endl;
    this->connectToHost();
    //TODO: set UP audio ????
}

void CallManager::endCall()
{
    this->_inCall = false;
    this->_udpClient->disconnect();
    _pairs.clear();
    //TODO: disable audio ????

    QObject::disconnect(this, SIGNAL(sendData()), this, SLOT(sendAudioData()));
}

#include "moc_CallManager.cpp"
